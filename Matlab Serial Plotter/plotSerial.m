close all;
clear all;
clc;
% close open serial ports 
delete(instrfindall);

% create serial object
s = serial("COM3", "BaudRate", 115200);

% open serial port
fopen(s);

i = 1;

figure
ylim([-100 100]);


while(1)
   line = fscanf(s);
   data = strsplit(strip(line),"/");
   disp(data);
   disp(length(data));
   if i > 3 % string array too small if starting from first index
       pitch(i) = str2double(data(1));
       roll(i) = str2double(data(2));
       yaw(i) = str2double(data(3));

       plot(pitch);
       hold on
       plot(roll);
       hold on
       plot(yaw);
       hold off
       if i <= 150
            xlim([3 i]);
       else
            xlim([i-100 i]); % runs across the x axis after ~100 reads
       end
       ylim([-100 100]);
       % change xlim to make it slide along after a certain point
       % adding a legend makes it lag badly
   end 
   
   i = i + 1;
   
   pause(0.03)
    
 end
