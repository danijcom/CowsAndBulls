#pragma once
#include "string"
#include "cassert"
#include "map"
#include "memory"

//Идентификаторы текстур
namespace Textures {
	enum ID {
		Background,
		Cloud1,
		Cloud2,
		Cloud3,
		AboutText,
		Wings,
		Placeholder,
		ButtonNumber,
		ButtonExit,
		ButtonAbout,
		ScoreRow,
		ScoreRowWin,
		ScoreRowLose,
		PopupSuccess,
		PopupInfo,
		PopupError,
		YouWon,
		YouLost
	};
}

//Идентификаторы шрифтов
namespace Fonts {
	enum ID {
		LotusMono
	};
}

//Шаблонный класс - хранилище ресурсов
template <class Resource, class Identifier>
class ResourceHolder {
private:
	//Словарь ссылок на ресурсы
	std::map<Identifier, std::unique_ptr<Resource>> resources;

public:
	//Конструктор
	ResourceHolder() {}

	//Загрузить ресурс (идентификатор, имя файла)
	void load(Identifier id, const std::string& filename);
	//Вернуть ссылку на ресурс по его идентификатору
	Resource& get(Identifier id);
};

template <class Resource, class Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	//Создаем указатель на новый обьект
	std::unique_ptr<Resource> resource(new Resource());

	//Загружаем ресурс по указанному имени файла
	if (!resource->loadFromFile(filename)) {
		throw std::exception(("ResourceHolder::load: Failed to load a texture [" + filename + "]").c_str());
	}

	//insert возвращает пару: итератор, показывающий на вставленный объект
	// и bool об успешности вставки
	auto inserted = resources.insert(std::make_pair(id, std::move(resource)));

	//Если false, значит ошибка
	assert(inserted.second);
}

template <class Resource, class Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	//Возвращает итератор найденного обекта
	auto found = resources.find(id);
	//Или end, если объект не найден
	assert(found != resources.end());

	//Возвращается std::pair, нас интересует второй объект из пары
	return *found->second;
}