clc
clear
close all
detail = 3201; %level of detail you want
a = linspace(-1.6,1.6,detail); %imaginary axis
b = linspace(-2,1.2,detail); %real axis
B = zeros(detail,detail,3); %for color mapping (have plans with the 3 colors later)
% look at "the dark side of the mandelbrot on youtube
[x,y] = meshgrid(a,b); %to create the complex plane
C = y+x*i;              %creating the plane
X = C;                  %initial conditions (first iteration)
for n = 1:63                    %iterating
  X = X.^2 + C;               %calculating
  expl = find(abs(X)>2==1);   %finding exploded values
  X(expl) = 0;                %removing from iteration
  C(expl) = 0;                %removing from plane
  B(expl) = n;                %saving step value
end
B = B/max(max(max(B)));         %deviding by max value for correct color
image(B)                        %printing