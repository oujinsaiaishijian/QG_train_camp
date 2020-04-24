from sklearn.neural_network import MLPClassifier
import random
import numpy as np
import pickle
import gzip


class Network():
    '''
    sizes包含各层的神经元的数量，如果我们想创建一个在第一层有2个神经元，
    第二层有3个，最后一层有一个神经元的神经网络，就要输入[2,3,1]

    '''
    def __init__(self, sizes):
        self.num_layers = len(sizes)
        self.sizes = sizes
        # 随机初始化偏差b和权重w
        self.biases = [np.random.randn(y, 1) for y in sizes[1:]]
        self.weights = [np.random.randn(y, x)
                        for x, y in zip(sizes[:-1], sizes[1:])]

    # 前向传播
    def feedforward(self, a):
        for b, w in zip(self.biases, self.weights):
            a = sigmoid(np.dot(w, a) + b)
        return a

    # 随机梯度下降
    '''
    training_data 是一个代表着训练输入和对应的期望输出的元组（x,y）的列表。
    epochs和mini_batch_size是期望的训练的迭代次数和取样时所用的mini_batch块
    的大小，eta是学习率.如果可选参数test_data被提供，那么程序将会在每次训练迭代
    后评价网络，并输出局部进展
    '''
    def SGD(self, training_data, epochs, mini_batch_size, eta,
            test_data=None):

        if test_data:
            n_test = len(test_data)
        n = len(training_data)
        for j in range(epochs):
            random.shuffle(training_data)
            mini_batches = [
                training_data[k:k + mini_batch_size]
                for k in range(0, n, mini_batch_size)]
            for mini_batch in mini_batches:
                self.update_mini_batch(mini_batch, eta)
            if test_data:
                print("Epoch {0}: {1} / {2}".format(
                    j, self.evaluate(test_data), n_test))
            else:
                print("Epoch {0} complete".format(j))

    '''
    随机地将徐连数据打乱，然后分成适当大小的小块。然后对于每一个mini_batch用
    一次梯度下降。
    '''
    def update_mini_batch(self, mini_batch, eta):
        nabla_b = [np.zeros(b.shape) for b in self.biases]
        nabla_w = [np.zeros(w.shape) for w in self.weights]
        for x, y in mini_batch:
            # 这里就做了大部分的工作
            delta_nabla_b, delta_nabla_w = self.backprop(x, y)
            nabla_b = [nb + dnb for nb, dnb in zip(nabla_b, delta_nabla_b)]
            nabla_w = [nw + dnw for nw, dnw in zip(nabla_w, delta_nabla_w)]
        # 适当地更新self.weights和self.biases
        self.weights = [w - (eta / len(mini_batch)) * nw
                        for w, nw in zip(self.weights, nabla_w)]
        self.biases = [b - (eta / len(mini_batch)) * nb
                       for b, nb in zip(self.biases, nabla_b)]

    def backprop(self, x, y):
        """Return a tuple ``(nabla_b, nabla_w)`` representing the
        gradient for the cost function C_x.  ``nabla_b`` and
        ``nabla_w`` are layer-by-layer lists of numpy arrays, similar
        to ``self.biases`` and ``self.weights``."""
        nabla_b = [np.zeros(b.shape) for b in self.biases]
        nabla_w = [np.zeros(w.shape) for w in self.weights]
        # feedforward
        activation = x
        # list to store all the activations, layer by layer
        activations = [x]
        # list to store all the z vectors, layer by layer
        zs = []
        for b, w in zip(self.biases, self.weights):
            z = np.dot(w, activation) + b
            zs.append(z)
            activation = sigmoid(z)
            activations.append(activation)
        # backward pass
        # 差值
        delta = self.cost_derivative(activations[-1], y) * \
                sigmoid_prime(zs[-1])
        nabla_b[-1] = delta
        nabla_w[-1] = np.dot(delta, activations[-2].transpose())
        for l in range(2, self.num_layers):
            z = zs[-l]
            sp = sigmoid_prime(z)
            delta = np.dot(self.weights[-l + 1].transpose(), delta) * sp
            nabla_b[-l] = delta
            nabla_w[-l] = np.dot(delta, activations[-l - 1].transpose())
        return (nabla_b, nabla_w)

    def evaluate(self, test_data):
        test_results = [(np.argmax(self.feedforward(x)), y)
                        for (x, y) in test_data]
        return sum(int(x == y) for (x, y) in test_results)

    def cost_derivative(self, output_activations, y):
        """Return the vector of partial derivatives \partial C_x /
        \partial a for the output activations."""
        return (output_activations - y)


def sigmoid(z):
    return 1.0 / (1.0 + np.exp(-z))


# sigmoid函数的导数
def sigmoid_prime(z):
    return sigmoid(z) * (1 - sigmoid(z))


def main():
    import mnist_loader
    training_data, validation_data, test_data = mnist_loader.load_data_wrapper()
    # 设置一个有30个隐层神经元的神经网络
    net = Network([784, 30, 10])
    print("这是我的神经网络")
    # 学习30次迭代，迷你块大小为10，学习率为3.0，打印评估效果
    net.SGD(training_data, 30, 10, 3.0, test_data=test_data)

    print("这是sklearn的神经网络")

    # 加载数据
    fp = gzip.open('../data/mnist.pkl.gz', 'rb')
    training_data, valid_data, test_data = pickle.load(fp, encoding='iso-8859-1')
    x_training_data, y_training_data = training_data
    x_valid_data, y_valid_data = valid_data
    x_test_data, y_test_data = test_data

    # 将验证集和训练集合并
    x_training_data_final = np.vstack((x_training_data, x_valid_data))
    y_training_data_final = np.append(y_training_data, y_valid_data)

    mlp = MLPClassifier(solver='sgd', activation='relu', alpha=1e-4, hidden_layer_sizes=(50, 50), random_state=1,
                        max_iter=100, verbose=10, learning_rate_init=.1)

    # 训练模型
    mlp.fit(x_training_data_final, y_training_data_final)

    # 查看模型结果
    print("the score of mlp is", mlp.score(x_test_data, y_test_data))
    print("the loss of mlp is", mlp.loss_)

if __name__ == '__main__':
    main()
