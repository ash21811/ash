% view_mandlebrot21_Example.m MAJ 2021 
% Plots mandlebrot set at low resolution for testing
%
% Input: ascii data file containing four column vectors from mandelbrot grid:
% index_number x_coordinate y_coordinate in/out_value
% Note: column vectors are all of length nx*ny, spanning each point on the grid
% and start from lower left grid point (-2,-1) and end on upper right grid point (2,1)
%
% To Run: on the MATLAB command line enter: view_mandlebrot21_Example
% Note this assumes the data file mand_p5.field is in the current directory
% Type pwd on the MATLAB and ls to confirm the directory location and
% contents, respectively
%
% For help and tutorials on MATLAB: https://www.mathworks.com/help/matlab/
% For plots specifically: https://www.mathworks.com/help/matlab/graphics.html


%%%%%%%% Load and Plot the Result %%%%%%%%%%%%%%
dat1 = load('mand_p5.dat');
ind = dat1(:,1); % index (length nx*ny) goes from 0 to (nx*ny - 1)
x1 = dat1(:,2); % x coordinates gridded (length nx*ny)
y1= dat1(:,3); % y coordinates gridded (length nx*ny)
val1 = dat1(:,4); % in/out value at respective x,y coordinate
whos % lists variables in workspace
 
%%%%%%% Reshapes the column vectors into grid matrix for plotting %%%%%%%
xshape1 = reshape(x1,5,9);  % reshape x coordate array (5 is ny, 9 is nx)
yshape1 = reshape(y1,5,9); % resphape y coord array (5 is ny, 9 is nx)
valshape1 = reshape(val1,5,9); % reshape in/out value (5 is ny, 9 is nx)
 
%%%%%%%%% Make Plot of in/out value over the x,y grid %%%%%%%%%%%%%
figure(1)
%Use subplot (instead of plot) to plot multiple images on a page
% subplot(2,1,1) specifies figure layout of 2 rows x 1 column and this one is first one (top)
subplot(2,1,1), pcolor(xshape1,yshape1,valshape1), colorbar, title(['Low Res Mandlebrot For Testing: inc 0.5 (first plot)']), shading flat, 
xlabel('X coordinate'), ylabel('Y coordinate')

% subplot(2,1,2) specifies figure layout of 2 rows x 1 column and this one is second one (bottom)
subplot(2,1,2), pcolor(xshape1,yshape1,valshape1), colorbar, title(['Low Res Mandelbrot for Testing: inc 0.5 (second plot)']), shading flat, hold on
xlabel('X coordinate'), ylabel('Y coordinate')

