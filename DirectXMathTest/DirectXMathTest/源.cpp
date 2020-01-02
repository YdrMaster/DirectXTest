#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <Windows.h>
#include <iostream>

std::ostream &XM_CALLCONV operator<<(
    std::ostream &stream,
    DirectX::FXMVECTOR v) {

    DirectX::XMFLOAT4 dest;
    DirectX::XMStoreFloat4(&dest, v);

    stream << '['
           << dest.x << ", "
           << dest.y << ", "
           << dest.z << ", "
           << dest.w << ']';
    return stream;
}

std::ostream &XM_CALLCONV operator<<(
    std::ostream &stream,
    DirectX::FXMMATRIX m) {

    DirectX::XMFLOAT4 dest;
    for (auto i = 0; i < 4; ++i) {
        DirectX::XMStoreFloat4(&dest, m.r[i]);
        stream << std::endl
               << dest.x << '\t'
               << dest.y << '\t'
               << dest.z << '\t'
               << dest.w;
    }
    return stream;
}

int main() {
    std::cout << std::boolalpha;
    if (!DirectX::XMVerifyCPUSupport()) {
        std::cerr << "directx math not supported" << std::endl;
        return 0;
    }

    {
        auto p = DirectX::XMVectorZero(),
             q = DirectX::XMVectorSplatOne(),
             u = DirectX::XMVectorSet(1, 2, 3, 0),
             v = DirectX::XMVectorReplicate(-2.0f),
             w = DirectX::XMVectorSplatZ(u);

        std::cout << "p = " << p << std::endl
                  << "q = " << q << std::endl
                  << "u = " << u << std::endl
                  << "v = " << v << std::endl
                  << "w = " << w << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;
    {
        using namespace DirectX;
        auto n = XMVectorSet(1, 0, 0, 0),
             u = XMVectorSet(1, 2, 3, 0),
             v = XMVectorSet(-2, 1, -3, 0),
             w = XMVectorSet(.707f, .707f, 0, 0),

             a = u + v,
             b = u - v,
             c = 10 * u,
             l = XMVector3Length(u),

             d = XMVector3Normalize(u), s = XMVector3Dot(u, v),
             e = XMVector3Cross(u, v);

        XMVECTOR projW, prepW;
        XMVector3ComponentsFromNormal(&projW, &prepW, w, n);

        auto equal = XMVector3Equal(projW + prepW, w),
             notEqual = XMVector3NotEqual(projW + prepW, w);

        auto angleVec = XMVector3AngleBetweenVectors(projW, prepW);
        auto angleRadians = XMVectorGetX(angleVec);
        auto angleDegrees = XMConvertToDegrees(angleRadians);

        std::cout << "u           = " << u << std::endl
                  << "v           = " << v << std::endl
                  << "w           = " << w << std::endl
                  << "a = u + v   = " << a << std::endl
                  << "b = u - v   = " << b << std::endl
                  << "c = 10 u    = " << c << std::endl
                  << "d = u / |u| = " << d << std::endl
                  << "e = u x v   = " << e << std::endl
                  << "l = |u|     = " << l << std::endl
                  << "s = u . v   = " << s << std::endl
                  << "projW       = " << projW << std::endl
                  << "prepW       = " << prepW << std::endl
                  << "projW + prepW == w = " << equal << std::endl
                  << "projW + prepW != w = " << notEqual << std::endl
                  << "angle rad   = " << angleRadians << std::endl
                  << "angle deg   = " << angleDegrees << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;
    {
        auto l_u =
            DirectX::XMVectorGetX(
                DirectX::XMVector3Length(
                    DirectX::XMVector3Normalize(
                        DirectX::XMVectorSet(1, 1, 1, 0))));
        std::cout.precision(8);
        std::cout << "length = " << l_u << std::endl
                  << "length " << (l_u == 1.0f ? "is" : "is not") << " 1" << std::endl
                  << "length^(10^6) = " << powf(l_u, 1e6f) << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;
    {
        using namespace DirectX;
        auto a = XMMATRIX(1, 0, 0, 0,
                          0, 2, 0, 0,
                          0, 0, 4, 0,
                          1, 2, 3, 1),
             b = XMMatrixIdentity(),
             c = a * b,
             d = XMMatrixTranspose(a);
        auto det = XMMatrixDeterminant(a);
        auto e = XMMatrixInverse(&det, a),
             f = a * e;
        std::cout << "A =" << a << std::endl
                  << "B =" << b << std::endl
                  << "C =" << c << std::endl
                  << "D =" << d << std::endl
                  << "Det =" << det << std::endl
                  << "E =" << e << std::endl
                  << "F =" << f << std::endl;
    }
    return 0;
}
