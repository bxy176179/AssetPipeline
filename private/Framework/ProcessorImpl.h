#pragma once

#include <memory>
#include <string>
#include <vector>

namespace cd
{

class SceneDatabase;

}

namespace cdtools
{

class IConsumer;
class IProducer;

class ProcessorImpl final
{
public:
	ProcessorImpl() = delete;
	explicit ProcessorImpl(IProducer* pProducer, IConsumer* pConsumer, cd::SceneDatabase* pHostSceneDatabase = nullptr);
	ProcessorImpl(const ProcessorImpl&) = delete;
	ProcessorImpl& operator=(const ProcessorImpl&) = delete;
	ProcessorImpl(ProcessorImpl&&) = delete;
	ProcessorImpl& operator=(ProcessorImpl&&) = delete;
	~ProcessorImpl();

	const cd::SceneDatabase* GetSceneDatabase() const { return m_pCurrentSceneDatabase; }
	void Run();

	void SetValidateSceneDatabaseEnable(bool enable) { m_enableValidateSceneDatabase = enable; }
	bool IsValidateSceneDatabaseEnabled() const { return m_enableValidateSceneDatabase; }

	void SetDumpSceneDatabaseEnable(bool enable) { m_enableDumpSceneDatabase = enable; }
	bool IsDumpSceneDatabaseEnabled() const { return m_enableDumpSceneDatabase; }

	void SetCalculateAABBForSceneDatabaseEnable(bool enable) { m_enableCalculateAABBForSceneDatabase = enable; }
	bool IsCalculateAABBForSceneDatabaseEnabled() const { return m_enableCalculateAABBForSceneDatabase; }

	void SetFlattenSceneDatabaseEnable(bool enable) { m_enableFlattenSceneDatabase = enable; }
	bool IsFlattenSceneDatabaseEnabled() const { return m_enableFlattenSceneDatabase; }

	void SetCalculateConnetivityDataEnable(bool enable) { m_enableCalculateConnetivityData = enable; }
	bool IsCalculateConnetivityDataEnabled() const { return m_enableCalculateConnetivityData; }

	void AddExtraTextureSearchFolder(const char* pFolderPath) { m_textureSearchFolders.push_back(pFolderPath); }
	bool IsSearchMissingTexturesEnabled() const { return !m_textureSearchFolders.empty(); }

	void SetEmbedTextureFilesEnable(bool enable) { m_enableEmbedTextureFiles = enable; }
	bool IsEmbedTextureFilesEnabled() const { return m_enableEmbedTextureFiles; }

	void DumpSceneDatabase();
	void ValidateSceneDatabase();
	void CalculateAABBForSceneDatabase();
	void FlattenSceneDatabase();
	void CalculateConnetivityData();
	void SearchMissingTextures();
	void EmbedTextureFiles();

private:
	IProducer* m_pProducer = nullptr;
	IConsumer* m_pConsumer = nullptr;

	cd::SceneDatabase* m_pCurrentSceneDatabase;
	std::unique_ptr<cd::SceneDatabase> m_pLocalSceneDatabase;
	std::vector<std::string> m_textureSearchFolders;

	bool m_enableDumpSceneDatabase = true;
	bool m_enableValidateSceneDatabase = true;
	bool m_enableCalculateAABBForSceneDatabase = true;
	bool m_enableFlattenSceneDatabase = false;
	bool m_enableCalculateConnetivityData = false;
	bool m_enableEmbedTextureFiles = false;
};

}