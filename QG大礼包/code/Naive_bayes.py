import numpy as np


class NaiveBayes():

    def fit(self, X, y):
        self.X = X
        self.y = y
        self.classes = np.unique(y)
        self.parameters = {}
        for i, c in enumerate(self.classes):
            # 计算每个种类的平均值，方差，先验概率
            X_Index_c = X[np.where(y == c)]
            X_index_c_mean = np.mean(X_Index_c, axis=0, keepdims=True)
            X_index_c_var = np.var(X_Index_c, axis=0, keepdims=True)
            parameters = {"mean": X_index_c_mean, "var": X_index_c_var, "prior": X_Index_c.shape[0] / X.shape[0]}
            self.parameters["class" + str(c)] = parameters

    def _pdf(self, X, classes):
        # 一维高斯分布的概率密度函数
        # eps为防止分母为0
        eps = 1e-4
        mean = self.parameters["class" + str(classes)]["mean"]
        var = self.parameters["class" + str(classes)]["var"]

        # 取对数防止数值溢出
        # numerator.shape = [m_sample,feature]
        numerator = np.exp(-(X - mean) ** 2 / (2 * var + eps))
        denominator = np.sqrt(2 * np.pi * var + eps)

        # 朴素贝叶斯假设(每个特征之间相互独立)
        # P(x1,x2,x3|Y) = P(x1|Y)*P(x2|Y)*P(x3|Y),取对数相乘变为相加
        # result.shape = [m_sample,1]
        result = np.sum(np.log(numerator / denominator), axis=1, keepdims=True)

        return result.T

    def _predict(self, X):
        # 计算每个种类的概率P(Y|x1,x2,x3) =  P(Y)*P(x1|Y)*P(x2|Y)*P(x3|Y)
        output = []
        for y in range(self.classes.shape[0]):
            prior = np.log(self.parameters["class" + str(y)]["prior"])
            posterior = self._pdf(X, y)
            prediction = prior + posterior
            output.append(prediction)
        return output

    def predict(self, X):
        # 取概率最大的类别返回预测值
        output = self._predict(X)
        output = np.reshape(output, (self.classes.shape[0], X.shape[0]))
        prediction = np.argmax(output, axis=0)
        return prediction
