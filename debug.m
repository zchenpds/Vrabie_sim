p_sim = [P_sim.Data(1,1,end); 
    2*P_sim.Data(1,2,end); 
    2*P_sim.Data(1,3,end); 
    2*P_sim.Data(1,4,end); 
    P_sim.Data(2,2,end); 
    2*P_sim.Data(2,3,end); 
    2*P_sim.Data(2,4,end); 
    P_sim.Data(3,3,end); 
    2*P_sim.Data(3,4,end); 
    P_sim.Data(4,4,end)]; 

start = floor((size(x_sim.Data, 1)-2)/N) * N + 1;

result = ...
   [diag(x_sim.Data(start:end, :)*P_sim.Data(:,:,end)*(x_sim.Data(start:end, :))'), ...
    diag(x_sim.Data(start:end, :)*P*(x_sim.Data(start:end, :))'), ...
    (x_bar_sim.Data(start:end, :))*p_sim, ...
    V_sim.Data(start:end)];

rr = result(:, 1) - result(:, 2)