function J = computeCost(X, y, theta)
%COMPUTECOST Compute cost for linear regression
%   J = COMPUTECOST(X, y, theta) computes the cost of using theta as the
%   parameter for linear regression to fit the data points in X and y

% Initialize some useful values
m = length(y); % number of training examples

% You need to return the following variables correctly
J = 0;

% ====================== YOUR CODE HERE ======================
% Instructions: Compute the cost of a particular choice of theta
%               You should set J to the cost.

% computes the cost function, J(theta).
% (X * theta) -> matrix of values produced by the hypothesis 
% (X * theta - y).^2 ) -> a matrix containing the Squared Error values
% sum ( (X * theta - y).^2 ) -> add up the total errors produced by hypothesis
% sum ( (X * theta - y).^2 ) / (2 * m) -> divides the total by the number of
% training examples

J = sum ( (X * theta - y).^2 ) / (2 * m);


% =========================================================================

end
