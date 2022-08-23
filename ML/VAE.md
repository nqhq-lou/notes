---
title: VAE intro
tags: [ML/VAE]
---

Variational Autoencoder (VAE) is of a variety of variance.

This article is used to record some conclusions on VAE.

This article is to be continued.

# Presettings

- This article assumed that you have had the basic knowledge on VAE.
	- So let's skip this part!

## Basic Realization of VAE

The basic realization if based on `PyTorch`, and the dataset is `MNIST`.

```Python
# code copied from ref[1]
class VAE(nn.Module):
    def __init__(self):
        super(VAE, self).__init__()
        self.enc = nn.Sequential(
            nn.Linear(784, 400),
            nn.ReLU(),
        )
        self.enc_mu = nn.Linear(400, 20)
        self.enc_logvar = nn.Linear(400, 20)
        self.dec = nn.Sequential(
            nn.Linear(20, 400),
            nn.ReLU(),
            nn.Linear(400, 784),
        )

    def encode(self, x):
        x = self.enc(x)
        return self.enc_mu(x), self.enc_logvar(x)

    def reparameterize(self, mu, logvar):
        std = torch.exp(0.5*logvar)  # 0.5 mul is a must
        eps = torch.randn_like(std)
        return mu + eps*std

    def decode(self, z):
        h3 = F.relu(self.fc3(z))
        return torch.sigmoid(self.fc4(h3))  # back to [0,1) region

    def forward(self, x):
        mu, logvar = self.encode(x.view(1, -1))
        z = self.reparameterize(mu, logvar)
        return self.decode(z), mu, logvar

```

And according to the very first article (see ref[1]), the loss function should be (copied from ref[2])

```Python
def loss_function_original(recon_x, x, mu, logvar):
    BCE = F.binary_cross_entropy(recon_x, x.view(1, -1), reduction='sum')
    # KL divergence is: 0.5 * sum(1 + log(sigma^2) - mu^2 - sigma^2)
    KLD = -0.5 * torch.sum(1 + logvar - mu.pow(2) - logvar.exp())
    return BCE + KLD
```

## Modifications on VAE

Here are some questions that I am care about:

### Change BCE loss
How about replacing BCE loss with MAE or MSE loss?

- Both work better than BCE.
- MAE is of larger acutance, while there's still bluring strokes for MSE.

### Changing weight ratio

How about adding an ratio between BCE loss and KLD loss?

This is beta-VAE.


###  `mean` and `sum`

I think this is just right modifying the ratio of weight between BCE and KLD.

According to the very first article, the loss should be sum.

I suggest use beta-VAE instead of using mean and sum modifications.



## cVAE



## beta-VAE




## References
1. Kingma, D.P. and Welling, M. (2014) ‘Auto-Encoding Variational Bayes’, arXiv:1312.6114 [cs, stat] [Preprint]. Available at: http://arxiv.org/abs/1312.6114 (Accessed: 19 March 2022).
2. [鲁鹏's lecture (from bilibili)](https://www.bilibili.com/video/BV1Zq4y1h7Tu?spm_id_from=333.337.search-card.all.click)
3. [VAE中的损失函数-impact of the loss function (from zhihu)](https://zhuanlan.zhihu.com/p/345360992)

Be cautious! Do not change the sequence of indexes of references!
