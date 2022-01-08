close all;
clear all;
clc;

[R, G, B] = sphere;

red_euclidean_distance = 30; % change this to see change in radius. Originally 10.66
RED_red_r_euclidean = R*red_euclidean_distance;
RED_green_r_euclidean = G*red_euclidean_distance;
RED_blue_r_euclidean = B*red_euclidean_distance;
red_sphere = surf(RED_red_r_euclidean + 197.57, RED_green_r_euclidean + 42.86, RED_blue_r_euclidean + 40.43);
set(red_sphere,'FaceColor',[1 0 0],'FaceAlpha',0.1, 'DisplayName', 'red sphere');
axis equal;

hold on;

green_euclidean_distance = 19; % change this to see change in radius. Originally 21.31
GREEN_red_r_euclidean = R*green_euclidean_distance;
GREEN_green_r_euclidean = G*green_euclidean_distance;
GREEN_blue_r_euclidean = B*green_euclidean_distance;
green_sphere = surf(GREEN_red_r_euclidean + 106.41, GREEN_green_r_euclidean + 106.35, GREEN_blue_r_euclidean + 50.53);
set(green_sphere,'FaceColor',[0 1 0],'FaceAlpha',0.1, 'DisplayName', 'green sphere');
axis equal;

hold on;

blue_euclidean_distance = 15; % change this to see change in radius. Originally 7.74
BLUE_red_r_euclidean = R*blue_euclidean_distance;
BLUE_green_r_euclidean = G*blue_euclidean_distance;
BLUE_blue_r_euclidean = B*blue_euclidean_distance;
blue_sphere = surf(BLUE_red_r_euclidean + 63.14, BLUE_green_r_euclidean + 98.29, BLUE_blue_r_euclidean + 109);
set(blue_sphere,'FaceColor',[0 0 1],'FaceAlpha',0.1, 'DisplayName', 'blue sphere');
axis equal;

hold on;

blue_r = [61 61 69 65 59 62 65];
blue_g = [100 100 99 98 100 97 94];
blue_b = [111 111 104 104 113 111 108];
plot3(blue_r, blue_g, blue_b, 'o','MarkerFaceColor','blue','MarkerSize', 8, 'MarkerEdgeColor','black' , 'DisplayName', 'blue');

title('ebay colour data');
xlabel('R');
ylabel('G');
zlabel('B');

hold on;
grid on;

green_r = [109 111 107 109 112 107 108 107 111 103 108 98 87 116 111 100 105];
green_g = [105 104 107 106 104 106 105 107 102 109 106 112 115 98 105 110 107];
green_b = [50 50 50 50 50 51 51 51 51 50 50 50 52 51 50 49 50];
plot3(green_r, green_g, green_b, 'o','MarkerFaceColor','green','MarkerSize', 8, 'MarkerEdgeColor','black', 'DisplayName', 'green');

hold on;
grid on;

dark_green_r = [77];
dark_green_g = [108];
dark_green_b = [70];
plot3(dark_green_r, dark_green_g, dark_green_b, 'o','MarkerFaceColor','magenta','MarkerSize', 8, 'MarkerEdgeColor','black', 'DisplayName', 'dark green');

hold on;
grid on;

red_r = [199 201 189 200 199 195 200];
red_g = [42 41 49 41 42 44 41];
red_b = [40 39 42 40 41 41 40];
plot3(red_r, red_g, red_b, 'o','MarkerFaceColor','red','MarkerSize', 8, 'MarkerEdgeColor','black','DisplayName', 'red');

hold on;
grid on;

gravel_r = [104 98];
gravel_g = [82 82];
gravel_b = [59 57];
plot3(gravel_r, gravel_g, gravel_b, 'o','MarkerFaceColor','black','MarkerSize', 8, 'MarkerEdgeColor','black', 'DisplayName', 'gravel');

hold on;
grid on;

empty_r = [102];
empty_g = [98];
empty_b = [60];
plot3(empty_r, empty_g, empty_b, 'o','MarkerFaceColor','cyan','MarkerSize', 8, 'MarkerEdgeColor','black', 'DisplayName', 'empty');

hold on;
grid on;

screw_r = [130 133 135 119];
screw_g = [84 81 83 89];
screw_b = [50 49 47 53];
plot3(screw_r, screw_g, screw_b, 'o','MarkerFaceColor','#808080','MarkerSize', 8, 'MarkerEdgeColor','black', 'DisplayName', 'screw');

hold on;
grid on;

wood_r = [134 132 138 139 141 142 139 137 139 139 139 135 137 146 134 139 141];
wood_g = [81 82 79 79 78 77 78 79 79 78 79 80 79 79 82 78 77];
wood_b = [51 51 51 51 50 50 51 53 52 52 51 52 52 53 51 51 51];
plot3(wood_r, wood_g, wood_b, 'o','MarkerFaceColor', '#e3c099','MarkerSize', 8, 'MarkerEdgeColor','black', 'DisplayName', 'wood');

legend()