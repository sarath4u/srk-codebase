import numpy as np
import sys
import re
import pickle
import json
import timeit


def parseTextModel(model_txt, num_boost_rounds=100, max_depth=3):
    """
    Parse the model in text format to build a matrix
    The matrix contains a dictionary that pairs the
    conditions in each booster to the corresponding output
    
    Inputs
        model_txt       :   model in text format
        num_boost_rounds:   total no. of trees
        max_depth       :   depth of each tree
    
    Returns
        nodeMatDic      :   Matrix equivalent of the model
    """
    
    ## Parameters
    num_leaves       = 2**max_depth                             # theoretical total no. of leaves (output)
    num_nodes        = sum(2**ii for ii in range(max_depth))    # theoretical total no. of nodes (conditions)
    
    ## Build an empty matrix to store the conditions and leaves
    nodeMatDic = np.empty((num_boost_rounds, num_nodes+num_leaves), dtype=object)
    
    # Parse the text model
    nodelist  = []
    with open(model_txt, 'r') as fin:
        for ii, line in enumerate(fin):
            if line.startswith('booster'):
                booster = int(line.split('[')[1].split(']')[0])
                continue
            list_1  = line.split()
            node   = int(list_1[0].split(':')[0])
            nodelist.append(node)
            list_2 = list_1[0].split(':')[1]
            if '=' in list_2:
                key   = -1
                num_leaves += 1
                value = float(list_2.split('=')[1])
            else:
                condition = re.search(r"\[([^]]+)", line).group(1)
                keystr    = condition.split('<')[0] 
                key       = 0 if keystr == 'f0' else 1
                value     = float(condition.split('<')[1])
                gotonode  = int(list_1[1].split(',')[0].split('=')[1]) 
            nodeMatDic[booster, node] = {key:(value, gotonode)}
    return nodeMatDic

def condition_mapper(actual_value, model_value, node=0):
    """
    Compares the actual value with the
    model value and navigates to the 
    next node in the tree

    Inputs
        actual_value:   value from data
        model_value :   value in the model
        node        :   node from which the condition originates

    Returns
        Node to which the condition points
    """

    if actual_value < model_value[0]:
        return model_value[1] 
    else:
        return model_value[1] + 1

def keyFinder(conDict):
    """
    Finds the key name

    Inputs
        conDict:    condition at a node of the tree

    Return
        Key name
    """

    key = list(conDict.keys())[0]
    return key

def get_base_score(filename):
    """
    Gets the base score of the model. This value 
    is on which the model output is built upon. 
    It is the average of the train data outputs
    for regression.

    Input:
        filename: name of the pickled model

    Returns:
        Base score
    """

    ## Open pickled model
    if filename.split('.')[2] == 'pkl':
        model = pickle.load(open(filename, 'rb'))
    else:
        model = xgb.Booster()
        model.load_model(filename)
    return float(json.loads(model.save_config())["learner"]["learner_model_param"]["base_score"])
    

def frixgb(base_score=0.5, varDict={1:100, 2: 24,}, num_boost_rounds=100, max_depth=3):
    """
    Prediction function
    
    Inputs
        base_score      :   Base score
        varDict         :   Dictionary of feature name and value pairs
        num_boost_rounds:   total no. of trees
        max_depth       :   depth of each tree

    Returns
        result          :   model prediction
    """
    
    result = base_score
    for ii in range(num_boost_rounds):
        booster = ii
        node    = 0
        for jj in range(max_depth + 1):
            conDict = nodeMatDic[booster, node]
            key     = keyFinder(conDict)
            if key == -1: break
            node    = condition_mapper(varDict[key], conDict[key], node=node)
        result += conDict[key][0]
    return result

if __name__ == "__main__":
    
    ## Parameters
    model_txt        = 'treeModel.txt'    # model dumped as text
    model_pkl        = 'treeModel.pkl'    # pickled model
    model_jsn        = 'treeModel.json'   # json model
    num_boost_rounds = 65                 # total no. of trees
    max_depth        = 7                  # depth of each tree     
    
    ## Build the matrix from the text model
    nodeMatDic = parseTextModel(model_txt, num_boost_rounds=num_boost_rounds, max_depth=max_depth)
   
    ## Get base score
    base_score = get_base_score(model_pkl)

    
    varDict = {0:500, 1:1 }
    preds = frixgb(base_score, varDict, num_boost_rounds=58, max_depth=7)
    print(preds)

    varDict = {0:-500, 1:4 }
    preds = frixgb(base_score, varDict, num_boost_rounds=58, max_depth=7)
    print(preds)
    
