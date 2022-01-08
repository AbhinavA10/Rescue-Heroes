% Daniel, don't use these average values

% Average values for Red
R_R = 200;
R_G = 45;
R_B =  40;
% Average values for green
G_R = 110;
G_G = 105;
G_B = 50;
% Average values for Blue
B_R = 60;
B_G = 100;
B_B = 110;
% New Point / sensor value
R2 = 65;
G2 = 94;
B2 = 108;

distance_to_red = sqrt((R2-R_R)^2+(G2-R_G)^2+(B2-R_B)^2)
distance_to_green = sqrt((R2-G_R)^2+(G2-G_G)^2+(B2-G_B)^2)
distance_to_blue = sqrt((R2-B_R)^2+(G2-B_G)^2+(B2-B_B)^2)


% New Point / sensor value
R2 = 119;
G2 = 89;
B2 = 53;
display("2nd point")
distance_to_red = sqrt((R2-R_R)^2+(G2-R_G)^2+(B2-R_B)^2)
distance_to_green = sqrt((R2-G_R)^2+(G2-G_G)^2+(B2-G_B)^2)
distance_to_blue = sqrt((R2-B_R)^2+(G2-B_G)^2+(B2-B_B)^2)

