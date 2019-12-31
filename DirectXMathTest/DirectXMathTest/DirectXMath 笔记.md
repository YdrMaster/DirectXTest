# DirectXMath 笔记

## 目录

- [向量类型](#向量类型)

## 向量类型

- 运算类型
  - `DirectX::XMVECTOR`
  - 用于变量
  - 16 字节对齐
  - `typedef __m128 XMVECTOR`
- 存储类型：
  - `DirectX::XMFLOAT2` 二维向量
  - `DirectX::XMFLOAT3` 三维向量
  - `DirectX::XMFLOAT4` 四维向量
  - 用于结构体成员
- 参数类型
  - `DirectX::FXMVECTOR` 用于前 3 个 `DirectX::XMVECTOR` 参数
  - `DirectX::GXMVECTOR` 用于第 4 个 `DirectX::XMVECTOR` 参数
  - `DirectX::HXMVECTOR` 用于第 5、6 个 `DirectX::XMVECTOR` 参数
  - `DirectX::CXMVECTOR` 用于其他 `DirectX::XMVECTOR` 参数
- 常量类型
  - `DirectX::XMVECTORF32` 浮点常向量
  - `DirectX::XMVECTORI32` 整型常向量