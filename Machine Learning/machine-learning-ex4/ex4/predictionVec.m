function prediction = predictionVec(vec)

vec = vec(:)';                       % row vector
[value, p] = max(vec, [], 2);        % obtain index of max value
newVec = zeros((size(vec, 2)), 1);   % get a new vector of the same size
newVec(p) = 1;
prediction = newVec;

end
