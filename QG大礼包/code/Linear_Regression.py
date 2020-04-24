import numpy as np

from Evaluating import R_square


class SimpleLinearRegression:

    def __init__(self):
        self.a_ = None
        self.b_ = None

    # 最小二乘法的实现
    def fit(self, x_train, y_train):
        assert x_train.ndim == 1, "Simple Linear Regression can only solve single feature train data."
        assert len(x_train) == len(y_train), "the size of x_train must be equal to the size of y_train"

        x_mean = np.mean(x_train)
        y_mean = np.mean(y_train)

        num = (x_train - x_mean).dot(y_train - y_mean)
        d = (x_train - x_mean).dot(x_train - x_mean)

        self.a_ = num / d
        self.b_ = y_mean - self.a_ * x_mean
        # 规范
        return self

    def predict(self, x_predict):
        assert x_predict.ndim == 1, "Simple Linear Regression can only solve single feature train data."
        assert self.a_ is not None and self.b_ is not None, "you must fit the model before you predict"

        return np.array([self._predict(x) for x in x_predict])

    def _predict(self, x_single):
        return self.a_ * x_single + self.b_

    def score(self, x_test, y_test):
        y_predict = self.predict(x_test)
        return R_square(y_predict, y_test)

    def __repr__(self):
        return "SimpleLinearRegression()"


class LinearRegression:

    def __init__(self):
        self.coef_ = None  # coefficient:系数
        self.interception_ = None  # interception:截距
        self._theta = None

    # 我大·正规化方法必须拥有姓名！
    def fit_normal(self, X_train, y_train):

        assert X_train.shape[0] == y_train.shape[0], "the size of X_train must be equal to the size of y_train"

        X_b = np.hstack([np.ones((len(X_train), 1)), X_train])
        self._theta = np.linalg.inv(X_b.T.dot(X_b)).dot(X_b.T).dot(y_train)
        self.interception_ = self._theta[0]
        self.coef_ = self._theta[1:]

        return self

    # 梯度下降法是更加普适的方法啦，所以就直接叫fit了
    def fit(self, X_train, y_train, eta=0.01, n_iters=1e4):

        assert X_train.shape[0] == y_train.shape[0], "the size of X_train must be equal to the size of y_train"

        X_b = np.hstack([np.ones((len(X_train), 1)), X_train])
        initial_theta = np.zeros(X_b.shape[1])
        self._theta = self.gradient_descent(X_b, y_train, initial_theta, eta, n_iters, epsilon=1e-8)
        self.interception_ = self._theta[0]
        self.coef_ = self._theta[1:]

        return self

    def gradient_descent(self, X_b, y, initial_theta, eta, n_iters=1e4, epsilon=1e-8):
        theta = initial_theta
        cur_iter = 0
        while cur_iter < n_iters:
            gradient = self.dJ(theta, X_b, y)
            last_theta = theta
            theta = theta - eta * gradient

            if abs(self.J(theta, X_b, y) - self.J(last_theta, X_b, y)) < epsilon:
                break

            cur_iter += 1

        return theta

    # 代价函数其实就是mse啦
    def J(self, theta, X_b, y):
        try:
            return np.sum((y - X_b.dot(theta)) ** 2) / len(X_b)
        except:
            # 如果return没有成功，说明代价函数过大，可能是学习率太大导致梯度无限上升
            return float('inf')

    def dJ(self, theta, X_b, y):
        return X_b.T.dot(X_b.dot(theta) - y) * 2. / len(X_b)

    def predict(self, X_predict):
        assert self.coef_ is not None and self.interception_ is not None, "you must fit before you predict"
        assert X_predict.shape[1] == len(self.coef_), "the feature number of X_predict must be equal to X_train"

        X_b = np.hstack([np.ones((len(X_predict), 1)), X_predict])
        return X_b.dot(self._theta)

    def score(self, X_test, y_test):
        y_predict = self.predict(X_test)
        return R_square(y_test, y_predict)

    def __repr__(self):
        return "LinearRegression()"