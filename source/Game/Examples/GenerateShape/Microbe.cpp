
#include "Microbe.h"
#include "MicrobeBrain.h"
#include "MicrobeMouth.h"
#include "MicrobeMover.h"
#include "MicrobeEnergy.h"
#include "DNA.h"
#include  "Common/Help.h"
#include "Core.h"

using namespace microbe;

//	Microbe

Microbe::Microbe() {
}

Microbe::Microbe(const DnaPtr& dnaPtr) {
	_dnaPtr = dnaPtr;
}

Microbe::Microbe(const std::string& idDNA) {
	_dnaPtr = DNA::getByName(idDNA);
}

void Microbe::update() {
	for (auto& cellPtr : _childs) {
		if (cellPtr) {
			cellPtr->update();
		}
	}
}

void Microbe::generate(const MicrobeWptr& microbeWptr)
{
	if (!_dnaPtr || microbeWptr.expired()) {
		return;
	}
	
	for (auto& dnaCell : _dnaPtr->getCells())
	{
		switch (dnaCell.type)
		{
			case  Cell::BRAIN :
			{
				Cell* cell = new Brain(microbeWptr, dnaCell);
				_childs.emplace_back(cell); 
			} break;

			case  Cell::ENERGY:
			{
				Cell* cell = new Energy(microbeWptr, dnaCell);
				_childs.emplace_back(cell);
			} break;

			case  Cell::MOUTH:
			{
				Cell* cell = new Mouth(microbeWptr, dnaCell);
				_childs.emplace_back(cell);
			} break;

			case  Cell::MOVER:
			{
				Cell* cell = new Mover(microbeWptr, dnaCell);
				_childs.emplace_back(cell);
			};
		}
	}

	make();
	setTexture("Textures/Cell.png");
}

void Microbe::make()
{
	_count = (_childs.size() + 1) * 3;
	_points = new Point[_count];
	_texCoord = new TexCoord[_count];

	size_t index = 3;

	for (auto& cell : _childs) {
		if (cell) {
			makeData(index, *cell);
		}
	}

	Cell cellTemp;
	index = 0;
	makeData(index, cellTemp);
}

void Microbe::makeData(size_t& index, const Cell& cell)
{
	Point*	  points = &_points[index];
	TexCoord* texCoord = &_texCoord[index];

	float scale = cell._size;
	const float* const pos = cell._pos;

	for (size_t i = 0; i < 3; ++i) {
		points[i].data[0] = pointsStatic[i].data[0] * scale;
		points[i].data[1] = pointsStatic[i].data[1] * scale;
		points[i].data[2] = pointsStatic[i].data[2] * scale;

		points[i].data[0] += pos[0];
		points[i].data[1] += pos[1];
		points[i].data[2] += (pos[2] + (static_cast<float>(index) * 0.01f));
	}

	memcpy(texCoord, texCoordStatic, sizeof(TexCoord) * 3);

	index += 3;
}

//	static

Triangle::Point Microbe::pointsStatic[3] = {	-0.425f, -0.9f, 0.0f,
												0.575f, 0.0f, 0.0f,
												-0.425f, 0.9f, 0.0f };

Triangle::TexCoord Microbe::texCoordStatic[3] = {	1.715f, 0.0f,
													0.0f, 0.0f,
													0.0f, 1.715f };
std::vector<MicrobePtr> Microbe::_microbes;

void Microbe::updateMicrobes() {
	for (auto& micribePtr : _microbes) {
		if (micribePtr) {
			micribePtr->update();
		}
	}
}

void Microbe::clear() {
	_microbes.clear();
}

void Microbe::generateMicrobes()
{
	clear();

	for (int i = 0; i < 10; ++i)
	{
		Microbe* microbe = new Microbe("0000");
		MicrobePtr microbePtr = MicrobePtr(microbe);
		MicrobeWptr microbeWptr = microbePtr;
		microbe->generate(microbeWptr);

		microbe->setPos( {	help::random_f(-10.0f, 10.0f),
							help::random_f(-10.0f, 10.0f),
							1.5f} );

		_microbes.push_back(microbePtr);
	}
}
