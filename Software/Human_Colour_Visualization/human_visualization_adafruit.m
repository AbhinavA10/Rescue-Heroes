close all;
clear all;
clc;

colour_data = [
    "155486",...
    "185389",...
    "1A5389",...
    "1A5084",...
    "1E5189",...
    "1E4F83",...
    "204F81",...
    "214E7F",...
    "28517F",...
    "3B7533",...
    "437132",...
    "457437",...
    "457132",...
    "467437",...
    "467032",...
    "486F32",...
    "486e32",...
    "4B6D32",...
    "586C3D",...
    "586B4E",...
    "59543D",...
    "5C533C",...
    "5D5640",...
    "5D533C",...
    "5E523B",...
    "5E523B",...
    "5F523B",...
    "605440",...
    "60523B",...
    "60523B",...
    "60513A",...
    "625239",...
    "666B51",...
    "68523B",...
    "6A7845",...
    "704e39",...
    "704C34",...
    "9C2F2A",...
    "A02D28",...
    "A42B28",...
    "A62D2C",...
    "A62E2C",...
    "A62A26",...
    "A62A27",...
    "A72D2C",...
    "A72C2C",...
    "A82C2B",...
    ];

counter = 1;

for i = 1:7
    for j = 1:7
        title("adafruit colour data")
        rectangle('Position',[i j 1 1], 'FaceColor', '#' + colour_data(counter));
        counter = counter + 1;
    end
end