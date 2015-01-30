#include "editorcreator.h"


EditorCreator::EditorCreator(QObject *parent /*= 0*/)
	: QObject(parent)
{
}

EditorCreator::~EditorCreator()
{
}

ResourceEditor *EditorCreator::create()
{
	return nullptr;
}
