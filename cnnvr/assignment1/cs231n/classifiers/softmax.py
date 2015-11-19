import numpy as np
from random import shuffle

def softmax_loss_naive(W, X, y, reg):
  """
  Softmax loss function, naive implementation (with loops)
  Inputs:
  - W: C x D array of weights
  - X: D x N array of data. Data are D-dimensional columns
  - y: 1-dimensional array of length N with labels 0...K-1, for K classes
  - reg: (float) regularization strength
  Returns:
  a tuple of:
  - loss as single float
  - gradient with respect to weights W, an array of same size as W
  """
  # Initialize the loss and gradient to zero.
  loss = 0.0
  dW = np.zeros_like(W)

  #############################################################################
  # TODO: Compute the softmax loss and its gradient using explicit loops.     #
  # Store the loss in loss and the gradient in dW. If you are not careful     #
  # here, it is easy to run into numeric instability. Don't forget the        #
  # regularization!                                                           #
  #############################################################################
  K = W.shape[0]
  D, N = X.shape
  Y = np.eye(K)
  Y = Y[:, y]
  P = np.exp(np.dot(W, X))
  J = P[y, xrange(N)] / np.sum(P, axis=0)
  J = -np.sum(np.log(J)) / N
  J += 0.5 * reg * np.sum(W * W)
  loss = J

  P = P / np.sum(P, axis=0)
  dW += -np.dot(Y - P, X.T) / N
  dW += reg * W
  #############################################################################
  #                          END OF YOUR CODE                                 #
  #############################################################################

  return loss, dW


def softmax_loss_vectorized(W, X, y, reg):
  """
  Softmax loss function, vectorized version.

  Inputs and outputs are the same as softmax_loss_naive.
  """
  # Initialize the loss and gradient to zero.
  loss = 0.0
  dW = np.zeros_like(W)

  #############################################################################
  # TODO: Compute the softmax loss and its gradient using no explicit loops.  #
  # Store the loss in loss and the gradient in dW. If you are not careful     #
  # here, it is easy to run into numeric instability. Don't forget the        #
  # regularization!                                                           #
  #############################################################################
  K = W.shape[0]
  D, N = X.shape
  Y = np.eye(K)
  Y = Y[:, y]
  P = np.exp(np.dot(W, X))
  J = P[y, xrange(N)] / np.sum(P, axis=0)
  J = -np.sum(np.log(J)) / N
  J += 0.5 * reg * np.sum(W * W)
  loss = J

  P = P / np.sum(P, axis=0)
  dW += -np.dot(Y - P, X.T) / N
  dW += reg * W
  #############################################################################
  #                          END OF YOUR CODE                                 #
  #############################################################################

  return loss, dW
