## Prerequisites
1. Probability
	- Given event x, the probability is $p(x)$ or $q(x)$

1. Information
	- The less probability, the more information on about this event
	- For the information is kind of restriction
	- Or events with less probability is of larger uncertainty, which is described by information
$$
I(p) = - \log p(x)
$$

1. Shannon Entropy
	- The average of information against probability
	- The entropy is the average of information.
		- I cannot get the point so far.
$$
\begin{aligned}
H(p) & = \mathbb{E}_{x\sim p} [I(p)] \\
& = \sum p(x) I(p) \\
& = - \sum p(x) \log p(x)
\end{aligned}
$$

1. Cross Entropy
	- The average of information against probability of another event
	- Minimizing cross entropy is equivalent to maximizing likelihood.
$$
\begin{aligned}
H(p, q)
& = \mathbb{E}_{x\sim p} [I(q)] \\
& = \sum p(x) I(q) \\
& = - \sum p(x) \log q(x)
\end{aligned}
$$

1. KL divergence (Kullback-Leibler)
	- or Relative entropy, Information gain
	- Used to evaluate the approximation of two different distribution, I guess?
$$
\begin{aligned}
D_{KL}(p||q)
& = H(p, q) - H(p) \\
& = - \sum p(x) \log \dfrac{q(x)}{p(x)} \\
& = \sum p(x) \log \dfrac{p(x)}{q(x)}
\end{aligned}
$$

## Properties of KL divergence

1. Non-symmetry

1. non-negative

1. concave function

## Minimizing

$p(x)$ is reality based distribution.
Use $q_\phi(x)$ with parameter $\phi$ to approximate $p(x)$.

KL of two kinds:
- $D_{KL} (p||q)$: the KL from q to p, or forward KL (from approximation to reality)
- $D_{KL} (q||p)$: the KL from p to q, or reversed KL (from reality to approximation)

### Forward KL

$$
\begin{aligned}
\mathrm{argmin}_\theta D_{KL} (P||Q_\theta)
& = \mathrm{argmin}_\theta \mathbb{E}_{x\sim p} [\log \dfrac{p(x)}{q_\theta (x)}] \\
& = \mathrm{argmin}_\theta ( \mathbb{E}_{x\sim p} [- \log q_\theta (x)] - H(p(x)) ) \\
& = \mathrm{argmin}_\theta H(p, q) \qquad & \text{(cross entropy)} \\
& = \mathrm{argmax}_\theta \mathbb{E}_{x\sim p} [\log q_\theta (x)] \qquad & \text{(MLE)}
\end{aligned}
$$

Obviously it equals to minimizing the cross entropy, or a maximum likelihood estimation.

So this is actually a inclusive / mean-seeking / mass-covering process.

But forward KL is sometimes hard to be optimized. See to the 3rd ref.



### Reverse KL

$$
\begin{aligned}
\mathrm{argmin}_\theta D_{KL} (q_\theta||P)
& = \mathrm{argmin}_\theta \mathbb{E}_{x\sim q_\theta} [\log \dfrac{q_\theta (x)}{p(x)}] \\
& = \mathrm{argmin}_\theta \mathbb{E}_{x\sim q_\theta} [- \log p(x)] - H(q_\theta (x)) \\
& = \mathrm{argmax}_\theta ( \mathbb{E}_{x\sim q_\theta} [\log p(x)] + H(q_\theta (x)) ) \qquad & \text{(Cross Entropy / MLE and Shannon Entropy)}
\end{aligned}
$$

The result would be like somewhat a exclusive / model-seeking / zero-forcing process.

The MLE makes q large where p is large, and the Shannon Entropy adds restrictions that q is better if less concentrated.

The gradient of reverse KL is easy to calculate, which is
$$
\sum_x \nabla[q_\theta (x)] (\log q_\theta (x) - \log p(x))
$$

### Gossip

Mnemonic: "When the truth comes first, you get the whole truth" (h/t Philip Resnik). Here "whole truth" corresponds to the inclusiveness of $D_{KL}(P||Q_\theta)$.

## Illustration

### Presettings

Use a Gaussian to approximate a biPeak gauss-like function

functions
```Mathematica
GaussPDF[x_, \[Mu]_, \[Sigma]_] := 
 1/(Sqrt[2 \[Pi]] \[Sigma]) Exp[-(x - \[Mu])^2/(2 \[Sigma]^2)](*被逼近的分布p(x)*)
f := GaussPDF[x, a, b](*进行逼近的分布q(x)*)
```

distribution $p(x)$
```mathematica
p[x_] := 1*GaussPDF[x, -3, 1] + 1.2*GaussPDF[x, 2, 1]
pc = Re[Integrate[p[x], {x, -\[Infinity], \[Infinity]}]];
Plot[p[x], {x, -10, 10}]
```

![file](http://106.14.196.28/wp-content/uploads/2022/03/image-1647868962781.png)

### MSE

```mathematica
solSD = Quiet@
  FindMinimum[
   Evaluate@NIntegrate[(f - p[x]/pc)^2, {x, -10, 10}], {a, b}]
Plot[{p[x]/pc, f /. solSD[[2]]}, {x, -10, 10}]

Out:={0.0491915, {a -> -0.0517579, b -> 3.38177}}
```

![file](http://106.14.196.28/wp-content/uploads/2022/03/image-1647869032285.png)

### Forward KL

```mathematica
solKL1 = Quiet@
  FindMinimum[
   NIntegrate[p[x]/pc Log[p[x]/pc/Abs@f], {x, -10, 10}], {a, b}]
Plot[{p[x]/pc, f /. solKL1[[2]]}, {x, -10, 10}]

Out:={0.315043, {a -> -0.272727, b -> 2.68297}}
```
![file](http://106.14.196.28/wp-content/uploads/2022/03/image-1647869075166.png)

### Reverse KL

```mathematica
solKL2 = Quiet@
  FindMinimum[
   NIntegrate[Abs@f*Log[Abs@f/(p[x]/pc)], {x, -10, 10}], {a, b}]
Plot[{p[x]/pc, Abs@f /. solKL2[[2]]}, {x, -10, 10}]

Out:={0.583179, {a -> 1.90802, b -> 1.11239}}
```

![file](http://106.14.196.28/wp-content/uploads/2022/03/image-1647868828633.png)

```mathematica
solKL2 = Quiet@
  FindMinimum[
   NIntegrate[Abs@f*Log[Abs@f/(p[x]/pc)], {x, -10, 10}], {{a, -3}, b}]
Plot[{p[x]/pc, Abs@f /. solKL2[[2]]}, {x, -10, 10}]

Out:={0.757031, {a -> -2.85005, b -> 1.1751}}
```

![file](http://106.14.196.28/wp-content/uploads/2022/03/image-1647868836505.png)

## References
- [KL-Divergence详解](https://zhuanlan.zhihu.com/p/425693597)
- [Reverse vs Forward KL](https://www.tuananhle.co.uk/notes/reverse-forward-kl.html)
	- A Python code is provided for illustration.
- [KL-divergence as an objective function](https://timvieira.github.io/blog/post/2014/10/06/kl-divergence-as-an-objective-function/)
	- Derivate of gradient of KL, and comments.
- [KL Divergence for Machine Learning - The objective of life is just to minimize a KL objective.](https://dibyaghosh.com/blog/probability/kldivergence.html)
	- More insights about ML.
	- Interesting perspectives: Supervised Learning <==> Forward KL, Reinforcement Learning <==> Reverse KL.
	- Which I might make a update based on this blog later.





