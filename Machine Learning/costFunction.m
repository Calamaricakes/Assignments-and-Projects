function J = costFunction(X, y, theta)

m = size(X, 1);                     % get m training examples from first dimension (m * n)

prediction = X * theta;             % get the predictions from the model given theta

squaredError = (prediction - y).^2;  % obtain the difference between prediction
                                    % and the data

J =  1/(2 * m) * sum(squaredError);   % obtain the value of the cost function
