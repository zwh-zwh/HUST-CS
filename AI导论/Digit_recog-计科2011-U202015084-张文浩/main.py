import numpy as np
import csv
import load
import matplotlib.pyplot as plt
import network

x_train, t_train0 = load.loadTrainData()
t_train = load.one_hot_label(t_train0)
x_test = load.loadTestData()
network = network.Network(input_size=784, hidden_size=50, output_size=10)

train_size = x_train.shape[0]
num = 40000
batch_size = 400
learning_rate = 0.2
epoch = max(train_size / batch_size, 1)

train_acc_list = []
i = 0
train_acc = 0

for i in range(num):
    batch_mask = np.random.choice(train_size, batch_size)
    x_batch = x_train[batch_mask]
    t_batch = t_train[batch_mask]
    train_acc = network.train(x_batch, t_batch, learning_rate)
    if i % epoch == 0:
        train_acc_list.append(train_acc)
        print("train acc:" + str(train_acc))

markers = {'train': 'o'}
x = np.arange(len(train_acc_list))
plt.plot(x, train_acc_list, label='train acc')
plt.xlabel("epochs")
plt.ylabel("accuracy")
plt.ylim(0, 1.0)
plt.legend(loc='lower right')
plt.show()


num = []
result = []
for i in range(28000):
    num.append(i+1)
    y = network.predict(x_test[i])
    result.append(np.argmax(y))


with open("submission.csv","w",newline="") as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(["ImageId", "Label"])
    for i in range(28000):
        writer.writerow([num[i], result[i]])


