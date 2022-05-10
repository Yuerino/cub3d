# Clone project

Clone the whole project including submodules

```bash
git clone --depth 1 --recurse-submodules https://github.com/Yuerino/cub3d.git
```

Or if you already cloned the project without submodules, use following command to pull the submodules

```bash
git submodule update --init --recursive --depth 1
```
