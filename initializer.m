clear;
A_nom = [-.0665, 8, 0, 0;
    0, -3.663, 3.663, 0;
    -6.86, 0, -13.736, -13.736;
    0.6, 0, 0, 0];

A = [-.0665, 11.5, 0, 0;
    0, -2.5, 2.5, 0;
    -9.5, 0, -13.736, -13.736;
    0.6, 0, 0, 0];
B = [0; 0; 13.736; 0];
C = eye(4);
D = zeros(4,1);

Q = eye(4);
R = eye(1);

% x0 = [0; 1; 0; 1];
x0 = [0; 1e-1; 0; 0];
% x0 = [-0.0413    0.0005    0.0156    0.0231]';
T = 0.05;
N = 20;
start = 2;

P = are(A, B/R*B', Q);
K = R\B'*P;

P_nom = are(A_nom, B/R*B', Q);
K_nom = R\B'*P_nom;