%=======================================================================================%
%         AN ISOPARAMETRIC FINITE ELEMENT SOLUTION ON A STRUCTURED MESH                 %
%=======================================================================================%

Lx = 10;                                                  % Length in the x direction
Ly = 10;                                                  % Length in the y direction
Lz = 10;                                                  % Length in the z direction
nx = 15;                                                  % no of divisions in x
ny = 15;                                                  % no of divisions in y
nz = 15;                                                  % no of divisions in z

xcord = linspace(0,Lx,nx);                                % x co-ordinates
ycord = linspace(0,Ly,ny);                                % y co-ordinates
zcord = linspace(0,Lz,nz);                                % z co-ordinates

nodalcords = combvec(xcord, ycord, zcord)';               % nodal coordinates
n_elmnts = (nx-1) * (ny-1) * (nz-1);                      % no of elements
elements = zeros(n_elmnts, 8);                            % elements
force = 1;

% ====================================================================================== %

% Elemenets and Nodes*

for j = 1 : n_elmnts
     q1 = fix((j - 1) / ((nx - 1) * (ny - 1)));
     q2 = fix((j - q1*((nx - 1) * (ny - 1)) - 1) / (nx - 1));
     elements(j, 1) = q2 + j - q1*((nx - 1) * (ny - 1))+ q1 * nx * ny;
     elements(j, 2) = q2 + j - q1*((nx - 1) * (ny - 1))+ q1 * nx * ny + 1;
     elements(j, 3) = q2 + j - q1*((nx - 1) * (ny - 1))+ q1 * nx * ny + 1 + nx;
     elements(j, 4) = q2 + j - q1*((nx - 1) * (ny - 1))+ q1 * nx * ny + nx;
     elements(j, 5) = q2 + j - q1*((nx - 1) * (ny - 1))+ q1 * nx * ny + nx * ny;
     elements(j, 6) = q2 + j - q1*((nx - 1) * (ny - 1))+ q1 * nx * ny + 1 + nx * ny;
     elements(j, 7) = q2 + j - q1*((nx - 1) * (ny - 1))+ q1 * nx * ny + 1 + nx + nx * ny;
     elements(j, 8) = q2 + j - q1*((nx - 1) * (ny - 1))+ q1 * nx * ny + nx + nx * ny;
end
 
% Nodal Vector
nodevec = (1 : nx * ny * nz)';

% ======================================================================================= %
% 
%%% Boundaries
%    ________
%   /  BT   /|
%  /_______/ |
% |        | BR
% |   BF   | |   
% |        | /
% |________|/

% 
BF = 1: nx * ny;
BA = nx * ny * (nx - 1) + 1 : ny * nx * nz;
BR = nx : nx : ny * nx * nz;
BL = 1: nx : ny * nx * nz;
BT = [];
BB = [];
for ii = 1 : nx * ny * nz / nz / ny 
    BT = [BT (nx * (ny - 1) * ii + (ii - 1) * nx + 1)  : ii * nx * ny];
    BB = [BB 1 + (ii - 1) * nx * ny: nx + (ii - 1) * nx * ny];
end

% 1. Dirichlet BCs

% % Change here for different BCs
%bndrynds = unique([BF BR BA BL BB BT])';    % nodes on Dirichlet boundary
bndrynds = unique([BR])';           % nodes on Dirichlet boundary
% 
cnt = 1;
nonbndrynds = zeros(size(nodevec, 1) - size(bndrynds, 1), 1);  % nodes not on the Dirichlet boundary
for nn = 1 : nx * ny * nz
    res = ismember(nn, bndrynds);
    if res == 0
        nonbndrynds(cnt) = nn;
        cnt = cnt + 1;
    end
end

% 2. Nuemann BCs

trn = -1;                                                        %% traction
%Nubounds = {'top' 'bottom' 'right' 'left' 'front' 'back'};
Nubounds = {'top' 'bottom' 'left' 'front' 'back'};
%Nubounds = {'top'};
Nubound = [];
Nuele = zeros(1,8);
eleTracMat = zeros(size(elements));

% ==================================================================================================== %

elmatpos = (combvec (1 : 8, 1 : 8))';

k = diag(ones(1,3));                                       % element stiffness matrix
wg = 1;                                                    % Weights
gp = [-0.5774   -0.5774   0.5774;
       0.5774   -0.5774   0.5774;
       0.5774    0.5774   0.5774;              
      -0.5774    0.5774   0.5774;
      -0.5774   -0.5774  -0.5774;
       0.5774   -0.5774  -0.5774;
       0.5774    0.5774  -0.5774;              
      -0.5774    0.5774  -0.5774 ];                             % Gauss Points
K = zeros(nx * ny * nz);                                        % Stiffness Matrix for assembly
F = zeros(nx * ny * nz, 1);                                     % Force vector for assembly
Traction = zeros(nx * ny * nz, 1);

% ==================================================================================================== %


% ELEMENTAL COMPUTATIONS

for i = 1 : 1 : n_elmnts
    el = elements(i, :);

% Isoparametric Shape Functions
%   (-1,1,-1)8______7(1,1,-1)
%           /|     /|
% (-1,1,1)4/_|____3(1,1,1)
%          | |    | |
% (-1,-1,-1|)5____|_6(1,-1,-1)    
%          |/     |/ 
% (-1,-1,1)1______2(1,-1,1)

% N1 = (1-eps)(1-hota)(1+zeta)/8 %
% N2 = (1+eps)(1-hota)(1+zeta)/8 %
% N3 = (1+eps)(1+hota)(1+zeta)/8 %
% N4 = (1-eps)(1+hota)(1+zeta)/8 %
% N5 = (1-eps)(1-hota)(1-zeta)/8 %
% N6 = (1+eps)(1-hota)(1-zeta)/8 %
% N7 = (1+eps)(1+hota)(1-zeta)/8 %
% N8 = (1-eps)(1+hota)(1-zeta)/8 %

% Je = [(x21-x43+x65-x87)/8+(-x21-x43-x65-x87)hota/8+(x21-x43-x65+x87)zeta/8+(-x21-x43+x65+x87)hota.zeta/8...
%       (x31+x42+x75+x86)/8+(-x21-x43-x65-x87)eps/8 +(x31+x42-x75-x86)zeta/8+(-x21-x43+x65+x87) eps.zeta/8...
%       (x51+x62+x73+x84)/8+(x21-x43-x65+x87) eps/8 +(x31+x42-x75-x86)hota/8+(-x21-x43+x65+x87) eps.hota/8... ]

% Je is not constant 

    x1 = nodalcords(el(1),1);
    y1 = nodalcords(el(1),2);
    z1 = nodalcords(el(1),3);
    x2 = nodalcords(el(2),1);
    y2 = nodalcords(el(2),2);
    z2 = nodalcords(el(2),3);
    x3 = nodalcords(el(3),1);
    y3 = nodalcords(el(3),2);
    z3 = nodalcords(el(3),3);
    x4 = nodalcords(el(4),1);
    y4 = nodalcords(el(4),2);
    z4 = nodalcords(el(4),3);
    x5 = nodalcords(el(5),1);
    y5 = nodalcords(el(5),2);
    z5 = nodalcords(el(5),3);
    x6 = nodalcords(el(6),1);
    y6 = nodalcords(el(6),2);
    z6 = nodalcords(el(6),3);
    x7 = nodalcords(el(7),1);
    y7 = nodalcords(el(7),2);
    z7 = nodalcords(el(7),3);
    x8 = nodalcords(el(8),1);
    y8 = nodalcords(el(8),2);
    z8 = nodalcords(el(8),3);
    
    x21 = x2 - x1;
    x43 = x4 - x3;
    x65 = x6 - x5;
    x87 = x8 - x7;
    x31 = x3 - x1;
    x42 = x4 - x2;
    x75 = x7 - x5;
    x86 = x8 - x6;
    x51 = x5 - x1;
    x62 = x6 - x2;
    x73 = x7 - x3;
    x84 = x8 - x4;
    
    y21 = y2 - y1;
    y43 = y4 - y3;
    y65 = y6 - y5;
    y87 = y8 - y7;
    y31 = y3 - y1;
    y42 = y4 - y2;
    y75 = y7 - y5;
    y86 = y8 - y6;
    y51 = y5 - y1;
    y62 = y6 - y2;
    y73 = y7 - y3;
    y84 = y8 - y4;
    y32 = y3 - y2;
    y76 = y7 - y6;
    y85 = y8 - y5;
    y41 = y4 - y1;
    
    z21 = z2 - z1;
    z43 = z4 - z3;
    z65 = z6 - z5;
    z87 = z8 - z7;
    z31 = z3 - z1;
    z42 = z4 - z2;
    z75 = z7 - z5;
    z86 = z8 - z6;
    z51 = z5 - z1;
    z62 = z6 - z2;
    z73 = z7 - z3;
    z84 = z8 - z4;
    z54 = z5 - z4;
    z81 = z8 - z1;
    z32 = z3 - z2;
    z76 = z7 - z6;
    
    for pt = 1 : 1 : size(gp)
        N = [(1 - gp(pt, 1)) * (1 - gp(pt, 2)) * (1 + gp(pt, 3))/ 8 ...
             (1 + gp(pt, 1)) * (1 - gp(pt, 2)) * (1 + gp(pt, 3))/ 8 ...
             (1 + gp(pt, 1)) * (1 + gp(pt, 2)) * (1 + gp(pt, 3))/ 8 ...
             (1 - gp(pt, 1)) * (1 + gp(pt, 2)) * (1 + gp(pt, 3))/ 8 ...
             (1 - gp(pt, 1)) * (1 - gp(pt, 2)) * (1 - gp(pt, 3))/ 8 ...
             (1 + gp(pt, 1)) * (1 - gp(pt, 2)) * (1 - gp(pt, 3))/ 8 ...
             (1 + gp(pt, 1)) * (1 + gp(pt, 2)) * (1 - gp(pt, 3))/ 8 ...
             (1 - gp(pt, 1)) * (1 + gp(pt, 2)) * (1 - gp(pt, 3))/ 8 ];

        
        Je = [(x21-x43+x65-x87)/8+(-x21-x43-x65-x87)*gp(pt, 2)/8+(x21-x43-x65+x87)*gp(pt, 3)/8+(-x21-x43+x65+x87)*gp(pt, 2)*gp(pt, 3)/8 ...
              (y21-y43+y65-y87)/8+(-y21-y43-y65-y87)*gp(pt, 2)/8+(y21-y43-y65+y87)*gp(pt, 3)/8+(-y21-y43+y65+y87)*gp(pt, 2)*gp(pt, 3)/8 ...
              (z21-z43+z65-z87)/8+(-z21-z43-z65-z87)*gp(pt, 2)/8+(z21-z43-z65+z87)*gp(pt, 3)/8+(-z21-z43+z65+z87)*gp(pt, 2)*gp(pt, 3)/8;
              (x31+x42+x75+x86)/8+(-x21-x43-x65-x87)*gp(pt, 1)/8+(x31+x42-x75-x86)*gp(pt, 3)/8+(-x21-x43+x65+x87)*gp(pt, 1)*gp(pt, 3)/8 ...
              (y31+y42+y75+y86)/8+(-y21-y43-y65-y87)*gp(pt, 1)/8+(y31+y42-y75-y86)*gp(pt, 3)/8+(-y21-y43+y65+y87)*gp(pt, 1)*gp(pt, 3)/8 ...
              (z31+z42+z75+z86)/8+(-z21-z43-z65-z87)*gp(pt, 1)/8+(z31+z42-z75-z86)*gp(pt, 3)/8+(-z21-z43+z65+z87)*gp(pt, 1)*gp(pt, 3)/8;
              (x51+x62+x73+x84)/8+(x21-x43-x65+x87) *gp(pt, 1)/8+(x31+x42-x75-x86)*gp(pt, 2)/8+(-x21-x43+x65+x87)*gp(pt, 1)*gp(pt, 2)/8 ... 
              (y51+y62+y73+y84)/8+(y21-y43-y65+y87) *gp(pt, 1)/8+(y31+y42-y75-y86)*gp(pt, 2)/8+(-y21-y43+y65+y87)*gp(pt, 1)*gp(pt, 2)/8 ...
              (z51+z62+z73+z84)/8+(z21-z43-z65+z87) *gp(pt, 1)/8+(z31+z42-z75-z86)*gp(pt, 2)/8+(-z21-z43+z65+z87)*gp(pt, 1)*gp(pt, 2)/8 ];
            
        Jin = inv(Je);

% Be = J^(-1) *  [ -(1-hota)(1+zeta)/8 (1-hota)(1+zeta)/8  (1+hota)(1+zeta)/8 -(1+hota)(1+zeta)/8 -(1-hota)(1-zeta)/8 (1-hota)(1-zeta)/8 (1+hota)(1-zeta)/8 -(1+hota)(1-zeta)/8
%                  -(1-eps)(1+zeta)/8 -(1+eps)(1+zeta)/8   (1+eps)(1+zeta)/8   (1-eps)(1+zeta)/8  -(1-eps)(1-zeta)/8 -(1+eps)(1-zeta)/8  (1+eps)(1-zeta)/8   (1-eps)(1-zeta)/8 
%                   (1-eps)(1-hota)/8  (1+eps)(1-hota)/8   (1+eps)(1+hota)/8   (1-eps)(1+hota)/8  -(1-eps)(1-hota)/8 -(1+eps)(1-hota)/8 -(1+eps)(1+hota)/8  -(1-eps)(1+hota)/8 ]    not a constant

        Be = (Jin/8)*[-(1-gp(pt,2))*(1+gp(pt,3))  (1-gp(pt,2))*(1+gp(pt,3))... 
                       (1+gp(pt,2))*(1+gp(pt,3)) -(1+gp(pt,2))*(1+gp(pt,3))...
                      -(1-gp(pt,2))*(1-gp(pt,3))  (1-gp(pt,1))*(1-gp(pt,3))...
                       (1+gp(pt,2))*(1-gp(pt,3)) -(1+gp(pt,1))*(1-gp(pt,3));  
                      -(1-gp(pt,1))*(1+gp(pt,3)) -(1+gp(pt,1))*(1+gp(pt,3))...    
                       (1+gp(pt,1))*(1+gp(pt,3))  (1-gp(pt,1))*(1+gp(pt,3))... 
                      -(1-gp(pt,1))*(1-gp(pt,3)) -(1+gp(pt,1))*(1-gp(pt,3))...
                       (1+gp(pt,1))*(1-gp(pt,3))  (1-gp(pt,1))*(1-gp(pt,3));
                       (1-gp(pt,1))*(1-gp(pt,2))  (1+gp(pt,1))*(1-gp(pt,2))...  
                       (1+gp(pt,1))*(1+gp(pt,2))  (1-gp(pt,1))*(1+gp(pt,2))... 
                      -(1-gp(pt,1))*(1-gp(pt,2)) -(1+gp(pt,1))*(1-gp(pt,2))...
                      -(1+gp(pt,1))*(1+gp(pt,2)) -(1-gp(pt,1))*(1+gp(pt,2))];

% *******   ********   ******** %
%  Stiffness Matrix generation  %
% *******   ********   ******** %                  
              
%      __ 
%      \ 
% Ke = /_ wg.Be'.k.Be.|Je|                     % element stiffness matrix
       
        Ke = wg * Be' * k * Be * det(Je);
%      __ 
%      \ 
% fe = /_ wg.N.|Je|                             element force vector
        
        fe = wg * N' * det(Je);
    end
    
    matpos = (combvec(el,el))';
    
    % ======================================== %
    %%% Applying traction
    
    eleTrac = zeros(8, 1);

    res = ismember('front', Nubounds);
    if res == 1
        Nubound = BF;
        for mm = 1 : 8
            logi = ismember(elements(1, mm), Nubound);
            if logi ~= 0
                Nuele(1, mm) = 1;
                logi = 0;
            end
        end
        NNu = 2* Nuele(1, :) .* N;
        gp_ = [(Nuele(1,:).*gp(:,1)')' (Nuele(1,:).*gp(:,2)')' (Nuele(1,:).*gp(:,3)')'];
        C = ((y31+y42)-gp_(pt,1)*(y21+y43))*((x21-x43)-gp_(pt,2)*(x21+x43))/16;
        eleTrac = trn * (eleTrac + NNu' * C);
        res = 0;
        Nuele = zeros(1,8);
    end
    %%%%%%
    res = ismember('bottom', Nubounds);
    if res == 1
        Nubound = BB;
        for mm = 1 : 8
            logi = ismember(elements(i, mm), Nubound);
            if logi ~= 0
                Nuele(1, mm) = 1;
                logi = 0;
            end
        end
        NNu = 2* Nuele(1, :) .* N;
        gp_ = [(Nuele(1,:).*gp(:,1)')' (Nuele(1,:).*gp(:,2)')' (Nuele(1,:).*gp(:,3)')'];
        C = -((x21+x65)+gp_(pt,3)*(x21-x65))*((z73+z84)+gp_(pt,1)*(z21-z65))/16;
        eleTrac = trn * (eleTrac + NNu' * C);
        res = 0;
        Nuele = zeros(1,8);
    end
    %%%%%
    res = ismember('top', Nubounds);
    if res == 1
        Nubound = BT;
        for mm = 1 : 8
            logi = ismember(elements(i, mm), Nubound);
            if logi ~= 0
                Nuele(1, mm) = 1;
                logi = 0;
            end
        end
        NNu = 2* Nuele(1, :) .* N;
        gp_ = [(Nuele(1,:).*gp(:,1)')' (Nuele(1,:).*gp(:,2)')' (Nuele(1,:).*gp(:,3)')'];
        C = -((x43+x87)+gp_(pt,3)*(x43-x87))*((z51+z62)+gp_(pt,1)*(z87-z43))/16;
        eleTrac = trn * (eleTrac + NNu' * C);
        res = 0;
        Nuele = zeros(1,8);
    end
    %%%%%%%
    res = ismember('back', Nubounds);
    if res == 1
        Nubound = BA;
        for mm = 1 : 8
            logi = ismember(elements(i, mm), Nubound);
            if logi ~= 0
                Nuele(1, mm) = 1;
                logi = 0;
            end
        end
        NNu = 2* Nuele(1, :) .* N;
        gp_ = [(Nuele(1,:).*gp(:,1)')' (Nuele(1,:).*gp(:,2)')' (Nuele(1,:).*gp(:,3)')'];
        C = -((y75+y86)-gp_(pt,1)*(y65+y87))*((x65-x87)-gp_(pt,2)*(x65+x87))/16;
        eleTrac = trn * (eleTrac + NNu' * C);
        res = 0;
        Nuele = zeros(1,8);
    end
    %%%%%%%
    res = ismember('right', Nubounds);
    if res == 1
        Nubound = BR;
        for mm = 1 : 8
            logi = ismember(elements(i, mm), Nubound);
            if logi ~= 0
                Nuele(1, mm) = 1;
                logi = 0;
            end
        end
        NNu = 2* Nuele(1, :) .* N;
        gp_ = [(Nuele(1,:).*gp(:,1)')' (Nuele(1,:).*gp(:,2)')' (Nuele(1,:).*gp(:,3)')'];
        C = ((y32+y76)+gp_(pt,3)*(y32-y76))*((z54+z81)+gp_(pt,2)*(z32-z76))/16;
        eleTrac = trn * (eleTrac + NNu' * C);
        res = 0;
        Nuele = zeros(1,8);
    end
    %%%%%%%%
    res = ismember('left', Nubounds);
    if res == 1
        Nubound = BL;
        for mm = 1 : 8
            logi = ismember(elements(i, mm), Nubound);
            if logi ~= 0
                Nuele(1, mm) = 1;
                logi = 0;
            end
        end
        NNu = 2* Nuele(1, :) .* N;
        gp_ = [(Nuele(1,:).*gp(:,1)')' (Nuele(1,:).*gp(:,2)')' (Nuele(1,:).*gp(:,3)')'];
        C = -((y85+y41)+gp_(pt,3)*(y41-y85))*((z73+z62)+gp_(pt,2)*(z51-z84))/16;
        eleTrac = trn * (eleTrac + NNu' * C);
        res = 0;
        Nuele = zeros(1,8);
    end
    %%%%%%%
    
%   Assembly of the stiffness matrix
%  
    for j = 1 : 1 : size(matpos,1)
        K(matpos(j, 1), matpos(j,2)) = K(matpos(j, 1), matpos(j,2)) ...
            + Ke(elmatpos(j, 1),elmatpos(j,2));
    end
    
% *******   ********   ******** %
%    Force vector generation    %
% *******   ********   ******** %

    for ii = 1 : size(elements, 1)
        F(elements(ii, :), 1) = F(elements(ii, :), 1) + fe(:, 1);
    end
     
    
    %%% Traction vector
    
    for jj = 1 : size(elements, 1)
        Traction(elements(jj, :), 1) = Traction(elements(jj, :), 1) + eleTrac(:, 1);
    end
end
% =============================================================================================== %

%%% Applying Dirichlet Boundary Condition

% Reducing the Stiffness matrix and the Force vector

for jj = size(bndrynds, 1): -1 :1
   K(bndrynds(jj), :) = [];
   K(:, bndrynds(jj)) = [];
   F(bndrynds(jj)) = [];
   Traction(bndrynds(jj)) = [];
end

%%% nodal solution

F = F + Traction;
u = K\F;

% Filling the dirichlet condition in the solution vector

temp = zeros(nx*ny*nz,1);
count = 1;
for kk = 1 : size(temp, 1)
    res = ismember(kk, nonbndrynds);
    if res == 1
        temp(kk, 1) = u(count, 1);
        count = count + 1;
    else
        temp(kk, 1) = 0.0;                  %% Dirichlet condition
    end
end

% Re-assembling in the Global solution Matrix

T = zeros(nx,ny,nz);
xn = 1;
yn = 1;
zn = 1;
count = 1;
cnt = 1;
while zn <= nz
    T(xn, yn, zn) = temp(count,1);
    if xn == nx
        yn = yn + 1;
        xn = 0;
    end
    if cnt == nx*ny
       xn = 0;
       yn = 1;
       zn = zn + 1;
       cnt = 0;
    end
    xn = xn + 1;
    count = count + 1;
    cnt = cnt + 1;
end

%================================================================================================%
