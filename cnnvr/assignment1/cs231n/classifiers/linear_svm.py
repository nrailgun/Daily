import numpy as np
from random import shuffle

def svm_loss_naive(W, X, y, reg):
  """
  Structured SVM loss function, naive implementation (with loops)
  Inputs:
  - W: C x D array of weights
  - X: D x N array of data. Data are D-dimensional columns
  - y: 1-dimensional array of length N with labels 0...K-1, for K classes
  - reg: (float) regularization strength
  Returns:
  a tuple of:
  - loss as single float
  - gradient with respect to weights W; an array of same shape as W
  """
  dW = np.zeros(W.shape) # initialize the gradient as zero

  # compute the loss and the gradient
  num_classes = W.shape[0]
  num_train = X.shape[1]
  loss = 0.0
  for i in xrange(num_train):
    scores = W.dot(X[:, i])
    correct_class_score = scores[y[i]]
    for j in xrange(num_classes):
      if j == y[i]:
        continue
      margin = scores[j] - correct_class_score + 1 # note delta = 1
      if margin > 0:
        loss += margin
      #loss += margin

  # Right now the loss is a sum over all training examples, but we want it
  # to be an average instead so we divide by num_train.
  loss /= num_train

  # Add regularization to the loss.
  #loss += 0.5 * reg * np.sum(W * W)

  #############################################################################
  # TODO:                                                                     #
  # Compute the gradient of the loss function and store it dW.                #
  # Rather that first computing the loss and then computing the derivative,   #
  # it may be simpler to compute the derivative at the same time that the     #
  # loss is being computed. As a result you may need to modify some of the    #
  # code above to compute the gradient.                                       #
  #############################################################################

  for i in xrange(num_train):
    scores = W.dot(X[:, i])
    correct_class_score = scores[y[i]]
    for j in xrange(num_classes):
      if j == y[i]:
        continue
      margin = scores[j] - correct_class_score + 1 # note delta = 1
      if margin <= 0:
        continue
      dW[j, :] += X[:, i]
      dW[y[i], :] -= X[:, i]
  dW /= num_train

  return loss, dW


def svm_loss_vectorized(W, X, y, reg):
  """
  Structured SVM loss function, vectorized implementation.

  Inputs and outputs are the same as svm_loss_naive.
  """
  loss = 0.0
  dW = np.zeros(W.shape) # initialize the gradient as zero

  #############################################################################
  # TODO:                                                                     #
  # Implement a vectorized version of the structured SVM loss, storing the    #
  # result in loss.                                                           #
  #############################################################################
  n_cls = W.shape[0]
  n_train = X.shape[1]

  Y = np.hstack([ np.eye(n_cls),
    np.zeros((n_cls, n_train - n_cls)) ])
  Y = Y[:, y] # Ground Truth

  WX = np.dot(W, X)
  WyX = WX[y, xrange(n_train)]
  l = WX - WyX + 1 - Y
  l = np.maximum.reduce([l, np.zeros_like(l)])
  loss = np.sum(l) / n_train
  #for i in xrange(n_train):
  #  xi = X[:, i]
  #  yi = y[i]
  #  l = np.dot(W, xi) - np.dot(W[yi, :], xi) + 1
  #  l = np.maximum.reduce([l, np.zeros_like(l)])
  #  l = np.sum(l) - 1
  #  loss += l
  #loss /= num_train
  #############################################################################
  #                             END OF YOUR CODE                              #
  #############################################################################


  #############################################################################
  # TODO:                                                                     #
  # Implement a vectorized version of the gradient for the structured SVM     #
  # loss, storing the result in dW.                                           #
  #                                                                           #
  # Hint: Instead of computing the gradient from scratch, it may be easier    #
  # to reuse some of the intermediate values that you used to compute the     #
  # loss.                                                                     #
  #############################################################################

  #WX = np.dot(W, X)
  #WyX = WX[y, xrange(n_train)]
  #l = WX - WyX + 1 - Y
  #l = np.maximum.reduce([l, np.zeros_like(l)])

  lb = np.array(l > 0, dtype=int) # k * m
  dW = np.dot(lb, X.T) # k * n

  dWy = X * np.sum(lb, 0) # n * m
  for i in xrange(n_cls):
    dW[i, :] -= np.sum(dWy[:, y == i], 1)

  dW /= n_train

  #############################################################################
  #                             END OF YOUR CODE                              #
  #############################################################################

  return loss, dW
