function [J, grad] = costFunctionReg(theta, X, y, lambda)
%COSTFUNCTIONREG Compute cost and gradient for logistic regression with regularization
%   J = COSTFUNCTIONREG(theta, X, y, lambda) computes the cost of using
%   theta as the parameter for regularized logistic regression and the
%   gradient of the cost w.r.t. to the parameters.

% Initialize some useful values
m = length(y); % number of training examples
grad = zeros(size(theta));

% ====================== YOUR CODE HERE ======================
% Instructions: Compute the cost of a particular choice of theta.
%               You should set J to the cost.
%               Compute the partial derivatives and set grad to the partial
%               derivatives of the cost w.r.t. each parameter in theta

sigmoid_output = sigmoid(X*theta);

partA = -(1/m)*( y'*log(sigmoid_output) + (1 - y')*log(1-sigmoid_output) );

theta_no0 = theta(2:size(theta,1),:);

partB = (lambda/(2*m))*theta_no0'*theta_no0;

J = partA + partB;

grad = ( 1/m ) * ( X'*(sigmoid_output - y) ) + (lambda/m)*theta;

% 1 to represent x0
grad(1) = (( 1/m ) * ( X'*(sigmoid_output - y) ))(1);

% =============================================================

end
