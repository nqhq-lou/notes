
- axis: YZX
- Euler angle: ZYZ
- irreps notation: `MxLp`, multiplicity, azimuthal number, parity 

### compare sequence between `e3nn` and `pyscf`
- [change of basis - e3nn](https://docs.e3nn.org/en/latest/guide/change_of_basis.html)
- 最后发现结果都是一样的, 说明数据是满足对称的
```Python
import numpy
numpy.set_printoptions(precision=4, formatter={'float': '{:.04f}'.format})
import pyscf
from pyscf.symm.Dmatrix import Dmatrix
import e3nn
from e3nn import o3

l = 3
irreps_input = o3.Irreps(f"{l}e")
angle = 0.3 * torch.eye(3)
  
for a in angle:
    d1 = irreps_input.D_from_angles(*a).numpy()
    d2 = Dmatrix(l, *a.numpy())
    print(f"{numpy.allclose(d1, d2)}, {d1.shape=}, {d2.shape=}")
```





