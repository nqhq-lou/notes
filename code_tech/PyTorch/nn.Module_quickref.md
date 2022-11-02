---
title: nn.Module quick reference
tags: [pytorch/nn_module]
---


## basic `nn.Module`s

### `nn.ConvNd`
- [nn.Conv3d doc](https://pytorch.org/docs/stable/generated/torch.nn.Conv3d.html)
- `padding_mode`
	- `zeros`: pad with zeros
		- **useful in molecule**
	- `reflect`: pad with reflect elements reflect by the edge
	- `replicate`: pad with the nearest the edge elements
		- what about corner of the image?
	- `circular`: pad elements from the other side
		- **useful in solid**




### `nn.BatchNormNd`




### `nn.Upsample`
- [nn.Upsample doc](https://pytorch.org/docs/stable/generated/torch.nn.Upsample.html)
- `align_corners`
- `mode`
	- `nearest`: the nearest point
	- `linear`: just linear
	- `bilinear`: 2d linear
	- `bicubic`: cubic interpolation
	- `trilinear`: 3d linear
	- `bi-` is only for 2d data, `tri-` is only for 3d data.
- for my project
	- in down/up sampling
	- `nn.Conv3d(ch, ch, kernel_size=4, stride=2, padding=1, padding_mode="circular")`
	- `nn.Upsample(scale_factor=2, mode='trilinear')`
	- in this way the data points in corresponding positions are matched.
![interpolation|400](https://upload.wikimedia.org/wikipedia/commons/thumb/9/90/Comparison_of_1D_and_2D_interpolation.svg/375px-Comparison_of_1D_and_2D_interpolation.svg.png)

- target pixels outside the source pixels are set to the `nearest` mode
![align_or_not|400](https://img2018.cnblogs.com/blog/1446032/201908/1446032-20190823152954205-86765483.png)




