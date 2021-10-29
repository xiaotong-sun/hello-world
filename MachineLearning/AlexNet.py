import torch
import torchvision
import torchvision.transforms as transforms
import ssl
import matplotlib.pyplot as plt
import numpy as np
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim

#-----------------------------------
# Show some of the training images.
def imshow(img):
    img = img / 2 + 0.5
    npimg = img.numpy()
    plt.imshow(np.transpose(npimg, (1, 2, 0)))
    plt.show()

#----------------------------------------
# Define a Convolutional Neural Network
class AlexNet(nn.Module):
    def __init__(self):
        super(AlexNet, self).__init__()

        self.cnn = nn.Sequential(
            # 卷积层1，3通道输入，96个卷积核，核大小7*7，步长2，填充2
            # 经过该层图像大小变为32-7+2*2 / 2 +1，15*15
            # 经3*3最大池化，2步长，图像变为15-3 / 2 + 1， 7*7
            nn.Conv2d(3, 96, 7, 2, 2),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(3, 2, 0),

            # 卷积层2，96输入通道，256个卷积核，核大小5*5，步长1，填充2
            # 经过该层图像变为7-5+2*2 / 1 + 1，7*7
            # 经3*3最大池化，2步长，图像变为7-3 / 2 + 1， 3*3
            nn.Conv2d(96, 256, 5, 1, 2),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(3, 2, 0),

            # 卷积层3，256输入通道，384个卷积核，核大小3*3，步长1，填充1
            # 经过该层图像变为3-3+2*1 / 1 + 1，3*3
            nn.Conv2d(256, 384, 3, 1, 1),
            nn.ReLU(inplace=True),

            # 卷积层3，384输入通道，384个卷积核，核大小3*3，步长1，填充1
            # 经过该层图像变为3-3+2*1 / 1 + 1，3*3
            nn.Conv2d(384, 384, 3, 1, 1),
            nn.ReLU(inplace=True),

            # 卷积层3，384输入通道，256个卷积核，核大小3*3，步长1，填充1
            # 经过该层图像变为3-3+2*1 / 1 + 1，3*3
            nn.Conv2d(384, 256, 3, 1, 1),
            nn.ReLU(inplace=True)
        )

        self.fc = nn.Sequential(
            # 256个feature，每个feature 3*3
            nn.Linear(256*3*3, 1024),
            nn.ReLU(),
            nn.Linear(1024, 512),
            nn.ReLU(),
            nn.Linear(512, 10)
        )

    def forward(self, x):
        x = self.cnn(x)

        # x.size()[0]: batch size
        x = x.view(x.size()[0], -1)
        x = self.fc(x)

        return x

if __name__ == '__main__':
    # -----------------------------------
    # Download the CIFAR10 dataset
    # In this dataset we have 60000 images,
    # in which 50000 images are training set and 10000 images are test set
    ssl._create_default_https_context = ssl._create_unverified_context
    transform = transforms.Compose(
        [transforms.ToTensor(),
         transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))]
    )

    batch_size = 8

    trainset = torchvision.datasets.CIFAR10(root='F:\CNN\data', train=True, download=True, transform=transform)
    trainloader = torch.utils.data.DataLoader(trainset, batch_size=batch_size, shuffle=True, num_workers=2)
    testset = torchvision.datasets.CIFAR10(root='F:\CNN\data', train=False, download=True, transform=transform)
    testloader = torch.utils.data.DataLoader(testset, batch_size=batch_size, shuffle=False, num_workers=2)

    classes = ('plane', 'car', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck')

    # # -----------------------------------
    # # Show some of the training images.
    # dataiter = iter(trainloader)  # get some random training images
    # images, labels = dataiter.next()
    # print(images.size())
    # imshow(torchvision.utils.make_grid(images))
    # print(' '.join('%5s' % classes[labels[j]] for j in range(batch_size)))

    # ----------------------------------------
    # Define a Convolutional Neural Network
    net = AlexNet()
    print(net)
    device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
    net.to(device)
    print(device)
    #--------------------------------------
    #Define a Loss function and optimizer
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.SGD(net.parameters(), lr=0.001, momentum=0.9)

    #------------------
    #Train the network
    Loss_temp = []
    Train_times = 20
    for epoch in range(Train_times):  # loop over the dataset multiple times
        running_loss = 0.0
        for i, data in enumerate(trainloader, 0):
            # get the inputs; data is a list of [inputs, labels]
            inputs, labels = data[0].to(device), data[1].to(device)

            # zero the parameter gradients
            optimizer.zero_grad()

            # forward + backward + optimize
            outputs = net(inputs)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()

            # print statistics
            running_loss += loss.item()
            if i % 1000 == 999:    # print every 2000 mini-batches
                print('[%d, %5d]' % (epoch + 1, i + 1))
        Loss_temp.append(running_loss / 6250)

    # Draw a line chart
    x = [i for i in range(1, Train_times + 1)]
    plt.plot(x, Loss_temp, 'o-', color='g', label="损失函数变化曲线")  # o-:圆形
    plt.xlabel("epoch")  # 横坐标名字
    plt.ylabel("LOSS")  # 纵坐标名字
    plt.savefig('F:\CNN\LossFunction_AlexNex.jpg')
    plt.show()


    PATH = 'F:\CNN\AlexNet.pth'
    torch.save(net.state_dict(), PATH)
    print('Finished Training')

