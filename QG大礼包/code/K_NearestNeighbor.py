import numpy as np
import math
from Evaluating import accuracy_score


class KNNClassifier:

    def __init__(self, k):
        assert k >= 1, "k must be valid"

        self.k = k
        self._X_train = None
        self._y_train = None

    def fit(self, X_train, y_train):
        assert X_train.shape[0] == y_train.shape[0], "the size of X_train must equal to the size of y_train"
        assert self.k <= X_train.shape[0], "the size of X_train must be at least k"

        self._X_train = X_train
        self._y_train = y_train
        return self

    def gaussian(self, distance, a=1, b=0, c=0.3):
        return a * math.e ** (-(distance - b) ** 2 / (2 * c ** 2))

    def predict(self, X_predict):
        # 给定向量X_predict,返回表示X_predict的结果向量，为此，还需要写一个_predict满足单个样本的预测功能
        assert self._X_train is not None and self._y_train is not None, "must fit before predict!"
        assert X_predict.shape[1] == self._X_train.shape[1], "the feature number of X_predict must be equal to X_train"

        y_predict = [self._predict(x) for x in X_predict]
        return np.array(y_predict)

    def _predict(self, x):
        # 给定单个预测数据x，返回x的预测结果值
        assert x.shape[0] == self._X_train.shape[1], "the feature number of x must be equal to X_train"

        # Calculating distance and preparing for vote,and i would like to optimize this algorithm a little
        distances = []
        for x_train in self._X_train:
            distance = np.sqrt(np.sum((x_train - x) ** 2))
            distances.append(distance)
        # "argsort" is used to sort from small to large
        nearest = np.argsort(distances)

        '''
                # 这一段是正常的，没有距离加权的
                topK_y = [self._y_train[i] for i in nearest[:self.k]]
                votes = Counter(topK_y)
                return votes.most_common(1)[0][0]
        '''

        # 这一段是我新写的距离加权的代码

        # taking the first k and I am going to weight those distances
        # Those are the first k label
        topK_y = [self._y_train[i] for i in nearest[:self.k]]
        # Those are the first k distances
        the_fist_k_distances = [self._X_train[i] for i in nearest[:self.k]]
        # The next three lines convert distance to weight
        weighted_distances = []
        for each in range(len(the_fist_k_distances)):
            weighted_distances.append(self.gaussian(the_fist_k_distances[each]))
        combined_data = {}
        '''
            错误样例！value在这里是字典
            if x not in combined_data:
                combined_data[x] = y
            else:
                combined_data[x] += y
        '''
        for x, y in zip(topK_y, weighted_distances):
            if x not in combined_data:
                combined_data[x] = y[0] + y[1]
            else:
                combined_data[x] += y[0] + y[1]
        predict_label = max(combined_data, key=combined_data.get)
        return predict_label

    def score(self, X_test, y_test):
        y_predict = self.predict(X_test)
        return accuracy_score(y_test, y_predict)

    def __repr__(self):
        return "KNN(k=%d)" % self.k