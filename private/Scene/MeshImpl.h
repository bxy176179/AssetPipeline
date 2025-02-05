#pragma once

#include "Base/Template.h"
#include "IO/InputArchive.hpp"
#include "IO/OutputArchive.hpp"
#include "Math/Box.hpp"
#include "Scene/Morph.h"
#include "Scene/VertexFormat.h"

#include <array>
#include <map>
#include <string>
#include <vector>

namespace cd
{

class MeshImpl final
{
public:
	MeshImpl() = delete;

	template<bool SwapBytesOrder>
	explicit MeshImpl(TInputArchive<SwapBytesOrder>& inputArchive)
	{
		*this << inputArchive;
	}

	explicit MeshImpl(uint32_t vertexCount, uint32_t polygonCount);
	explicit MeshImpl(MeshID meshID, std::string meshName, uint32_t vertexCount, uint32_t polygonCount);

	MeshImpl(const MeshImpl&) = delete;
	MeshImpl& operator=(const MeshImpl&) = delete;
	MeshImpl(MeshImpl&&) = default;
	MeshImpl& operator=(MeshImpl&&) = default;
	~MeshImpl() = default;

	void Init(uint32_t vertexCount, uint32_t polygonCount);
	void Init(MeshID meshID, std::string meshName, uint32_t vertexCount, uint32_t polygonCount);
	
	void SetID(MeshID id) { m_id = id; }
	MeshID GetID() const { return m_id; }

	void SetName(std::string name) { m_name = MoveTemp(name); }
	const std::string& GetName() const { return m_name; }

	uint32_t GetVertexCount() const { return m_vertexCount; }
	uint32_t GetPolygonCount() const { return m_polygonCount; }

	void SetVertexFormat(VertexFormat vertexFormat) { m_vertexFormat = MoveTemp(vertexFormat); }
	VertexFormat& GetVertexFormat() { return m_vertexFormat; }
	const VertexFormat& GetVertexFormat() const { return m_vertexFormat; }

	void SetAABB(AABB aabb) { m_aabb = MoveTemp(aabb); }
	AABB& GetAABB() { return m_aabb; }
	const AABB& GetAABB() const { return m_aabb; }

	void SetMaterialID(uint32_t materialIndex) { m_materialID = materialIndex; }
	MaterialID GetMaterialID() const { return m_materialID; }

	uint32_t GetMorphCount() const { return static_cast<uint32_t>(m_morphTargets.size()); }
	Morph& GetMorph(uint32_t morphIndex) { return m_morphTargets[morphIndex]; }
	const Morph& GetMorph(uint32_t morphIndex) const { return m_morphTargets[morphIndex]; }
	std::vector<Morph>& GetMorphs() { return m_morphTargets; }
	const std::vector<Morph>& GetMorphs() const { return m_morphTargets; }

	void SetVertexPosition(uint32_t vertexIndex, const Point& position);
	Point& GetVertexPosition(uint32_t vertexIndex) { return m_vertexPositions[vertexIndex]; }
	const Point& GetVertexPosition(uint32_t vertexIndex) const { return m_vertexPositions[vertexIndex]; }
	std::vector<Point>& GetVertexPositions() { return m_vertexPositions; }
	const std::vector<Point>& GetVertexPositions() const { return m_vertexPositions; }

	void SetVertexNormal(uint32_t vertexIndex, const Direction& normal);
	Direction& GetVertexNormal(uint32_t vertexIndex) { return m_vertexNormals[vertexIndex]; }
	const Direction& GetVertexNormal(uint32_t vertexIndex) const { return m_vertexNormals[vertexIndex]; }
	std::vector<Direction>& GetVertexNormals() { return m_vertexNormals; }
	const std::vector<Direction>& GetVertexNormals() const { return m_vertexNormals; }
	void ComputeVertexNormals();

	void SetVertexTangent(uint32_t vertexIndex, const Direction& tangent);
	Direction& GetVertexTangent(uint32_t vertexIndex) { return m_vertexTangents[vertexIndex]; }
	const Direction& GetVertexTangent(uint32_t vertexIndex) const { return m_vertexTangents[vertexIndex]; }
	std::vector<Direction>& GetVertexTangents() { return m_vertexTangents; }
	const std::vector<Direction>& GetVertexTangents() const { return m_vertexTangents; }
	void SetVertexBiTangent(uint32_t vertexIndex, const Direction& biTangent);
	Direction& GetVertexBiTangent(uint32_t vertexIndex) { return m_vertexBiTangents[vertexIndex]; }
	const Direction& GetVertexBiTangent(uint32_t vertexIndex) const { return m_vertexBiTangents[vertexIndex]; }
	std::vector<Direction>& GetVertexBiTangents() { return m_vertexBiTangents; }
	const std::vector<Direction>& GetVertexBiTangents() const { return m_vertexBiTangents; }
	void ComputeVertexTangents();

	void SetVertexUVSetCount(uint32_t setCount);
	uint32_t GetVertexUVSetCount() const { return m_vertexUVSetCount; }
	void SetVertexUV(uint32_t setIndex, uint32_t vertexIndex, const UV& uv);
	UV& GetVertexUV(uint32_t setIndex, uint32_t vertexIndex) { return m_vertexUVSets[setIndex][vertexIndex]; }
	const UV& GetVertexUV(uint32_t setIndex, uint32_t vertexIndex) const { return m_vertexUVSets[setIndex][vertexIndex]; }
	std::vector<UV>& GetVertexUVs(uint32_t uvSetIndex) { return m_vertexUVSets[uvSetIndex]; }
	const std::vector<UV>& GetVertexUVs(uint32_t uvSetIndex) const { return m_vertexUVSets[uvSetIndex]; }

	void SetVertexColorSetCount(uint32_t setCount);
	uint32_t GetVertexColorSetCount() const { return m_vertexColorSetCount; }
	void SetVertexColor(uint32_t setIndex, uint32_t vertexIndex, const Color& color);
	Color& GetVertexColor(uint32_t setIndex, uint32_t vertexIndex) { return m_vertexColorSets[setIndex][vertexIndex]; }
	const Color& GetVertexColor(uint32_t setIndex, uint32_t vertexIndex) const { return m_vertexColorSets[setIndex][vertexIndex]; }
	std::vector<Color>& GetVertexColors(uint32_t colorSetIndex) { return m_vertexColorSets[colorSetIndex]; }
	const std::vector<Color>& GetVertexColors(uint32_t colorSetIndex) const { return m_vertexColorSets[colorSetIndex]; }

	void SetVertexInfluenceCount(uint32_t influenceCount);
	uint32_t GetVertexInfluenceCount() const { return m_vertexInfluenceCount; }
	void SetVertexBoneWeight(uint32_t boneIndex, uint32_t vertexIndex, BoneID boneID, VertexWeight weight);
	BoneID& GetVertexBoneID(uint32_t boneIndex, uint32_t vertexIndex) { return m_vertexBoneIDs[boneIndex][vertexIndex]; }
	const BoneID& GetVertexBoneID(uint32_t boneIndex, uint32_t vertexIndex) const { return m_vertexBoneIDs[boneIndex][vertexIndex]; }
	std::vector<BoneID>& GetVertexBoneIDs(uint32_t boneIndex) { return m_vertexBoneIDs[boneIndex]; }
	const std::vector<BoneID>& GetVertexBoneIDs(uint32_t boneIndex) const { return m_vertexBoneIDs[boneIndex]; }
	VertexWeight& GetVertexWeight(uint32_t boneIndex, uint32_t vertexIndex) { return m_vertexWeights[boneIndex][vertexIndex]; }
	const VertexWeight& GetVertexWeight(uint32_t boneIndex, uint32_t vertexIndex) const { return m_vertexWeights[boneIndex][vertexIndex]; }
	std::vector<VertexWeight>& GetVertexWeights(uint32_t boneIndex) { return m_vertexWeights[boneIndex]; }
	const std::vector<VertexWeight>& GetVertexWeights(uint32_t boneIndex) const { return m_vertexWeights[boneIndex]; }

	uint32_t GetVertexAdjacentVertexCount(uint32_t vertexIndex) const { return static_cast<uint32_t>(m_vertexAdjacentVertexArrays[vertexIndex].size()); }
	void AddVertexAdjacentVertexID(uint32_t vertexIndex, VertexID vertexID);
	VertexIDArray& GetVertexAdjacentVertexArray(uint32_t vertexIndex) { return m_vertexAdjacentVertexArrays[vertexIndex]; }
	const VertexIDArray& GetVertexAdjacentVertexArray(uint32_t vertexIndex) const { return m_vertexAdjacentVertexArrays[vertexIndex]; }
	std::vector<VertexIDArray>& GetVertexAdjacentVertexArrays() { return m_vertexAdjacentVertexArrays; }
	const std::vector<VertexIDArray>& GetVertexAdjacentVertexArrays() const { return m_vertexAdjacentVertexArrays; }

	uint32_t GetVertexAdjacentPolygonCount(uint32_t vertexIndex) const { return static_cast<uint32_t>(m_vertexAdjacentPolygonArrays[vertexIndex].size()); }
	void AddVertexAdjacentPolygonID(uint32_t vertexIndex, PolygonID polygonID);
	PolygonIDArray& GetVertexAdjacentPolygonArray(uint32_t vertexIndex) { return m_vertexAdjacentPolygonArrays[vertexIndex]; }
	const PolygonIDArray& GetVertexAdjacentPolygonArray(uint32_t vertexIndex) const { return m_vertexAdjacentPolygonArrays[vertexIndex]; }
	std::vector<PolygonIDArray>& GetVertexAdjacentPolygonArrays() { return m_vertexAdjacentPolygonArrays; }
	const std::vector<PolygonIDArray>& GetVertexAdjacentPolygonArrays() const { return m_vertexAdjacentPolygonArrays; }

	void SetPolygon(uint32_t polygonIndex, cd::Polygon polygon);
	std::vector<Polygon>& GetPolygons() { return m_polygons; }
	const std::vector<Polygon>& GetPolygons() const { return m_polygons; }
	Polygon& GetPolygon(uint32_t polygonIndex) { return m_polygons[polygonIndex]; }
	const Polygon& GetPolygon(uint32_t polygonIndex) const { return m_polygons[polygonIndex]; }
	cd::VertexID GetPolygonVertexID(uint32_t polygonIndex, uint32_t vertexIndex) const;

	void MarkVertexInvalid(VertexID v);
	bool IsVertexValid(VertexID v) const;
	void SwapVertexData(VertexID v0, VertexID v1);
	void RemoveVertexData(VertexID v);

	void MarkPolygonInvalid(PolygonID p);
	bool IsPolygonValid(PolygonID p) const;
	void RemovePolygonData(PolygonID p);

	// After unify, all IDs cached by users should clean up.
	void Unify();

	template<bool SwapBytesOrder>
	MeshImpl& operator<<(TInputArchive<SwapBytesOrder>& inputArchive)
	{
		std::string meshName;
		uint32_t meshID;
		uint32_t meshMaterialID;
		uint32_t vertexCount;
		uint32_t vertexUVSetCount;
		uint32_t vertexColorSetCount;
		uint32_t vertexInfluenceCount;
		uint32_t polygonCount;

		inputArchive >> meshName >> meshID >> meshMaterialID
			>> vertexCount
			>> vertexUVSetCount >> vertexColorSetCount
			>> vertexInfluenceCount
			>> polygonCount;

		Init(MeshID(meshID), MoveTemp(meshName), vertexCount, polygonCount);
		SetMaterialID(meshMaterialID);
		SetVertexUVSetCount(vertexUVSetCount);
		SetVertexColorSetCount(vertexColorSetCount);
		SetVertexInfluenceCount(vertexInfluenceCount);

		inputArchive >> GetAABB();
		GetVertexFormat() << inputArchive;
		inputArchive.ImportBuffer(GetVertexPositions().data());
		inputArchive.ImportBuffer(GetVertexNormals().data());
		inputArchive.ImportBuffer(GetVertexTangents().data());
		inputArchive.ImportBuffer(GetVertexBiTangents().data());

		for (uint32_t uvSetIndex = 0U; uvSetIndex < GetVertexUVSetCount(); ++uvSetIndex)
		{
			inputArchive.ImportBuffer(GetVertexUVs(uvSetIndex).data());
		}

		for (uint32_t colorSetIndex = 0U; colorSetIndex < GetVertexColorSetCount(); ++colorSetIndex)
		{
			inputArchive.ImportBuffer(GetVertexColors(colorSetIndex).data());
		}

		for(uint32_t boneIndex = 0U; boneIndex < GetVertexInfluenceCount(); ++boneIndex)
		{
			inputArchive.ImportBuffer(GetVertexBoneIDs(boneIndex).data());
			inputArchive.ImportBuffer(GetVertexWeights(boneIndex).data());
		}

		inputArchive.ImportBuffer(GetPolygons().data());

		return *this;
	}

	template<bool SwapBytesOrder>
	const MeshImpl& operator>>(TOutputArchive<SwapBytesOrder>& outputArchive) const
	{
		outputArchive << GetName() << GetID().Data() << GetMaterialID().Data()
			<< GetVertexCount()
			<< GetVertexUVSetCount() << GetVertexColorSetCount()
			<< GetVertexInfluenceCount()
			<< GetPolygonCount();

		outputArchive << GetAABB();
		GetVertexFormat() >> outputArchive;
		outputArchive.ExportBuffer(GetVertexPositions().data(), GetVertexPositions().size());
		outputArchive.ExportBuffer(GetVertexNormals().data(), GetVertexNormals().size());
		outputArchive.ExportBuffer(GetVertexTangents().data(), GetVertexTangents().size());
		outputArchive.ExportBuffer(GetVertexBiTangents().data(), GetVertexBiTangents().size());

		for (uint32_t uvSetIndex = 0U; uvSetIndex < GetVertexUVSetCount(); ++uvSetIndex)
		{
			outputArchive.ExportBuffer(GetVertexUVs(uvSetIndex).data(), GetVertexUVs(uvSetIndex).size());
		}

		for (uint32_t colorSetIndex = 0U; colorSetIndex < GetVertexColorSetCount(); ++colorSetIndex)
		{
			outputArchive.ExportBuffer(GetVertexColors(colorSetIndex).data(), GetVertexColors(colorSetIndex).size());
		}

		for (uint32_t boneIndex = 0U; boneIndex < GetVertexInfluenceCount(); ++boneIndex)
		{
			outputArchive.ExportBuffer(GetVertexBoneIDs(boneIndex).data(), GetVertexBoneIDs(boneIndex).size());
			outputArchive.ExportBuffer(GetVertexWeights(boneIndex).data(), GetVertexWeights(boneIndex).size());
		}

		outputArchive.ExportBuffer(GetPolygons().data(), GetPolygons().size());

		return *this;
	}

private:
	uint32_t					m_vertexCount = 0U;
	uint32_t					m_vertexUVSetCount = 0U;
	uint32_t					m_vertexColorSetCount = 0U;
	uint32_t					m_vertexInfluenceCount = 0U;
	uint32_t					m_polygonCount = 0U;

	MeshID						m_id;
	MaterialID					m_materialID;
	std::string					m_name;
	AABB						m_aabb;

	// morph targets
	std::vector<Morph>			m_morphTargets;

	// vertex geometry data
	// TODO : Remove m_vertexFormat.
	// We can generate VertexFormat immediately based on current vertex data types.
	VertexFormat				m_vertexFormat;
	std::vector<Point>			m_vertexPositions;
	std::vector<Direction>		m_vertexNormals;		// Maybe we wants to use face normals? Or we can help to calculate it.
	std::vector<Direction>		m_vertexTangents;		// Ditto.
	std::vector<Direction>		m_vertexBiTangents;		// If not stored in model file, we can help to calculate it.

	// vertex texture data
	std::vector<UV>				m_vertexUVSets[MaxUVSetCount];
	std::vector<Color>			m_vertexColorSets[MaxColorSetCount];

	// vertex skin data
	std::vector<BoneID>			m_vertexBoneIDs[MaxBoneInfluenceCount];
	std::vector<VertexWeight>	m_vertexWeights[MaxBoneInfluenceCount];

	// vertex connectivity data
	// For geometry processing algorithms, it is common to query connectivity data.
	std::vector<VertexIDArray>	m_vertexAdjacentVertexArrays;
	std::vector<PolygonIDArray>	m_vertexAdjacentPolygonArrays;

	// editing data
	// During the process of removing vertices/polygons, it is difficult to maintain the relationship
	// which means id is same to index.
	std::map<VertexID, uint32_t> m_mapChaosVertexIDToIndex;
	std::map<PolygonID, uint32_t> m_mapChaosPolygonIDToIndex;

	// polygon data
	std::vector<Polygon>		m_polygons;
};

}