# XGBoost Model Export to Fortran

This is an example showing how a trained XGBoost model can be converted to a static Fortran function for embedding inside numerical solvers or HPC pipelines.

## Files

1. parseModel.py          : Python equivalent of the model
2. parse\_model\_mod.f90  : Fortran module that contains all the functions that can generate the model and make predictions
3. test\_parse\_model.f90 : Test program to check the functions
4. treeModel.pkl          : Binary version of the xgboost model
5. treeModel.txt          : Text version of the xgboost model
