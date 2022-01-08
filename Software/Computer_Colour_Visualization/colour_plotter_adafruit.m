close all;
clear all;
clc;

[R, G, B] = sphere;

red_euclidean_distance = 25; % change this to see change in radius. Originally 9.02
RED_red_r_euclidean = R*red_euclidean_distance;
RED_green_r_euclidean = G*red_euclidean_distance;
RED_blue_r_euclidean = B*red_euclidean_distance;
red_sphere = surf(RED_red_r_euclidean + 164.6, RED_green_r_euclidean + 44.3, RED_blue_r_euclidean + 41.8);
set(red_sphere,'FaceColor',[1 0 0],'FaceAlpha',0.1, 'DisplayName', 'red sphere');
axis equal;

hold on;

green_euclidean_distance = 19; % change this to see change in radius. Originally 14.05
GREEN_red_r_euclidean = R*green_euclidean_distance;
GREEN_green_r_euclidean = G*green_euclidean_distance;
GREEN_blue_r_euclidean = B*green_euclidean_distance;
green_sphere = surf(GREEN_red_r_euclidean + 69.22, GREEN_green_r_euclidean + 107.36, GREEN_blue_r_euclidean + 50.75);
set(green_sphere,'FaceColor',[0 1 0],'FaceAlpha',0.1, 'DisplayName', 'green sphere');
axis equal;

hold on;

blue_euclidean_distance = 25; % change this to see change in radius. Originally 12.12
BLUE_red_r_euclidean = R*blue_euclidean_distance;
BLUE_green_r_euclidean = G*blue_euclidean_distance;
BLUE_blue_r_euclidean = B*blue_euclidean_distance;
blue_sphere = surf(BLUE_red_r_euclidean + 29.11, BLUE_green_r_euclidean + 80.89, BLUE_blue_r_euclidean + 132.33);
set(blue_sphere,'FaceColor',[0 0 1],'FaceAlpha',0.1, 'DisplayName', 'blue sphere');
axis equal;

hold on;

blue_r = [24 26 21 40 30 30 26 32 33];
blue_g = [83 83 84 81 81 79 80 79 78];
blue_b = [137 137 134 127 137 131 132 129 127];
plot3(blue_r, blue_g, blue_b, 'o','MarkerFaceColor','blue','MarkerSize', 8, 'MarkerEdgeColor','black', 'DisplayName', 'blue');

title('adafruit colour data');
xlabel('R');
ylabel('G');
zlabel('B');

hold on;
grid on;

green_r = [70 69 70 69 75 59 72 72 67];
green_g = [116 116 112 113 109 117 111 110 113];
green_b = [55 55 50 50 50 51 50 50 50];
plot3(green_r, green_g, green_b, 'o','MarkerFaceColor','green','MarkerSize', 8, 'MarkerEdgeColor','black', 'DisplayName', 'green');

hold on;
grid on;


dark_green_r = [45];
dark_green_g = [111];
dark_green_b = [89];
plot3(dark_green_r, dark_green_g, dark_green_b, 'o','MarkerFaceColor','magenta','MarkerSize', 8, 'MarkerEdgeColor','black', 'DisplayName', 'dark green');

hold on;
grid on;

red_r = [167 168 166 166 167 164 166 156 166 160];
red_g = [45 44 45 46 44 43 42 47 42 45];
red_b = [44 43 44 44 44 40 38 42 39 40];
plot3(red_r, red_g, red_b, 'o','MarkerFaceColor','red','MarkerSize', 8, 'MarkerEdgeColor','black', 'DisplayName', 'red');

hold on;
grid on;


gravel_r = [104 98];
gravel_g = [82 82];
gravel_b = [59 57];
plot3(gravel_r, gravel_g, gravel_b, 'o','MarkerFaceColor','black','MarkerSize',8, 'MarkerEdgeColor','black', 'DisplayName', 'gravel');

hold on;
grid on;

sand_r = [112 112];
sand_g = [78 76];
sand_b = [57 52];
plot3(sand_r, sand_g, sand_b, 'o','MarkerFaceColor','#C2B280','MarkerSize', 8, 'MarkerEdgeColor','black', 'DisplayName', 'sand');

hold on;
grid on;

screw_r = [92 106 88 88];
screw_g = [83 120 108 107];
screw_b = [60 69 61 78];
plot3(screw_r, screw_g, screw_b, 'o','MarkerFaceColor','#808080','MarkerSize', 8, 'MarkerEdgeColor','black', 'DisplayName', 'screw');

hold on;
grid on;

wood_r = [93 102 96 94 96 96 96 95 94 93 89];
wood_g = [86 107 84 82 82 82 81 82 82 83 84];
wood_b = [64 81 64 59 59 59 58 59 59 60 61];
plot3(wood_r, wood_g, wood_b, 'o','MarkerFaceColor','#e3c099','MarkerSize', 8, 'MarkerEdgeColor','black', 'DisplayName', 'wood');

legend();

