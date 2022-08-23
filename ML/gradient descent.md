---
title: gradient descent
tags: [ML/GD]
---


# Gradient Descent

Vanilla, AdaGrad, RMSProp, momentum and Adam.

(base on HY Lee's Lecture, see [2021ML: 自动调整学习速率](https://www.bilibili.com/video/BV1JA411c7VT?p=7))

## Presettings

$$
f := f(x,\theta)
$$

$$
\theta = \mathrm{arg} \ \mathrm{min} \ f
$$

And step cnt `$ t $` start from 1.

## Plain

Introduce learning rate `$ \eta $`.

$$
\theta^{t+1} \leftarrow \theta^{t} - \eta \nabla_x f
$$

## Vanilla

Learning rate decrease by step cnt `$ t $`.

Learning rate is smaller for larger step cnt.

$$
\eta^t = \dfrac{\eta}{\sqrt{t}}
$$

$$
\theta^{t+1} \leftarrow \theta^{t} - \eta^t \nabla_x f
$$

## AdaGrad

Based on Vanilla, introduce accumulative parameter about gradient.

The step length is smaller for direction with larger gradient.

$$
\sigma_i^t = \sum_{\tau=1}^{t} (\nabla_{x_i} f)^2
$$

$$
\theta^{t+1}
\leftarrow \theta^{t} - \dfrac{\eta^t}{\sqrt{\sigma^t / t}} \nabla_x f
\Longleftrightarrow \theta^{t} - \dfrac{\eta}{\sqrt{\sigma^t}} \nabla_x f
$$

## Momentum

Introduce ratio `$ \beta $` to modify the applied gradient.

$$
g^t \leftarrow (1 - \beta)\nabla_x f + \beta g^{t-1}
$$

$$
\theta^{t+1} \leftarrow \theta^{t} - \eta g^t
$$

## RMSProp

Introduce accumulative parameter different from that of AdaGrad.

Another adaptive learning rate configuration with quick response to large growth in gradient magnitude.

$$
\sigma_i^t = \alpha \sigma_i^{t-1} + (1-\alpha) (\nabla_x f)^2
$$

$$
\theta_i^{t+1} \leftarrow \theta_i^{t} - \dfrac{\eta}{\sqrt{\sigma_i^t}} \nabla_x f
$$

## Adam

Adam = RMSProp + Momentum

see arxiv 1412.6980

$$
\theta_i^{t+1} \leftarrow \theta_i^{t} - \dfrac{\eta}{\sqrt{\sigma_i^t}} g^t
$$

## Code

Use Wolfram Mathematica

- Function

$$
f(x,y) = x^2 + y^2 / 1000
$$

```mathematica
f[{x_, y_}] := x^2 + y^2/1000
df[{x_, y_}] := Evaluate[FullSimplify@Map[D[f[{x, y}], #] &, {x, y}]]

landscape = Show[
ContourPlot[f[{x, y}], {x, -5, 5}, {y, -2, 50}, 
AxesLabel -> Automatic, Contours -> Range[0, 40]],
Graphics[{Red, PointSize[Large], Point[{0, 0}]}]]
```

![file](http://106.14.196.28/wp-content/uploads/2022/03/image-1647780470947.png)

- Use AdaGrad and momentum

```mathematica
pos = {{-3, 40}};(*init position*)
{\[Eta], \[Beta]} = {0.5, 0.9};(*learning rate, momentum*)
\[Sigma] = {0, 0};(*grad accum*)
gLast = {0, 0};(*store last grad*)
\[Sigma]List = {\[Sigma]};(*store sigma*)

For[i = 1, i <= 1000, i++,
 g = \[Beta]*gLast + (1 - \[Beta]) N@df[pos[[i]]];
 \[Sigma] += g^2;
 AppendTo[\[Sigma]List, \[Sigma]];
 temp = pos[[i]] - \[Eta]/Sqrt[\[Sigma]/i] g;
 AppendTo[pos, temp];
 gLast = g;
 ]

pltlb = "lr=" <> ToString[\[Eta]] <> ", momentum=" <> 
   ToString[\[Beta]];
GraphicsRow[{Show[landscape, 
   ListLinePlot[pos, PlotStyle -> {Orange}, PlotRange -> Full], 
   ImageSize -> Medium, PlotLabel -> pltlb],
  ListLogPlot[Transpose[\[Sigma]List/Range[Length[\[Sigma]List]]], 
   PlotTheme -> "Detailed", AspectRatio -> 1, 
   PlotLabel -> "\[Sigma] @ " <> pltlb, 
   PlotLegends -> {"\[Sigma]x", "\[Sigma]y"}, ImageSize -> 200]}]
```

- Examples

![file](http://106.14.196.28/wp-content/uploads/2022/03/image-1647781302471.png)

![file](http://106.14.196.28/wp-content/uploads/2022/03/image-1647781509931.png)

![file](http://106.14.196.28/wp-content/uploads/2022/03/image-1647781567066.png)

## Others

- Residual Network (arxiv 1512.03385)
	- `$lr = 0.01$` to warm up, then `$ lr = 0.1 $` for training.
- Transformer
	- special training parameter
