close all;
clear all;
clc;

% create serial object
s = serial("COM3", "BaudRate", 115200);

% open serial port
fopen(s);

i = 1;

figure
ylim([-100 100]);
while(1)
   
   data(i) = str2double(fscanf(s));
   plot(data);
   
   disp(data(i));
   i = i + 1;
   
   pause(0.03)
   drawnow; 
    
end
