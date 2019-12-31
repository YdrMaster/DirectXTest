#include <Windows.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>

std::ostream& XM_CALLCONV operator<<(
	std::ostream& stream,
	DirectX::FXMVECTOR v) {

	DirectX::XMFLOAT3 dest;
	DirectX::XMStoreFloat3(&dest, v);

	stream
		<< '('
		<< dest.x << ", "
		<< dest.y << ", "
		<< dest.z << ')';
	return stream;
}

int main() {
	std::cout << std::boolalpha;
	if (!DirectX::XMVerifyCPUSupport()) {
		std::cerr << "directx math not supported" << std::endl;
		return 0;
	}

	{
		DirectX::XMVECTOR
			p = DirectX::XMVectorZero(),
			q = DirectX::XMVectorSplatOne(),
			u = DirectX::XMVectorSet(1, 2, 3, 0),
			v = DirectX::XMVectorReplicate(-2.0f),
			w = DirectX::XMVectorSplatZ(u);

		std::cout
			<< "p = " << p << std::endl
			<< "q = " << q << std::endl
			<< "u = " << u << std::endl
			<< "v = " << v << std::endl
			<< "w = " << w << std::endl;
	}
	{
		using namespace DirectX;
		auto
			n = DirectX::XMVectorSet(1, 0, 0, 0),
			u = DirectX::XMVectorSet(1, 2, 3, 0),
			v = DirectX::XMVectorSet(-2, 1, -3, 0),
			w = DirectX::XMVectorSet(.707f, .707f, 0, 0),

			a = u + v,
			b = u - v,
			c = 10 * u,
			l = XMVector3Length(u),

			d = XMVector3Normalize(u),
			s = XMVector3Dot(u, v),
			e = XMVector3Cross(u, v);

		XMVECTOR projW, prepW;
		XMVector3ComponentsFromNormal(&projW, &prepW, w, n);

		auto
			equal = XMVector3Equal(projW + prepW, w),
			notEqual = XMVector3NotEqual(projW + prepW, w);

		auto angleVec = XMVector3AngleBetweenVectors(projW, prepW);
		auto angleRadians = XMVectorGetX(angleVec);
		auto angleDegrees = XMConvertToDegrees(angleRadians);

		std::cout
			<< "u           = " << u << std::endl
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
	
	return 0;
}
