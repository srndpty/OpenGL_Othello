#include "Game.h"



Game::Game()
{
	ResetBoard();
}


Game::~Game()
{
}

void Game::Draw(const int id)
{
	// �Ֆ�
	for (size_t i = 0; i < Game::FIELD_SIZE.y; i++)
	{
		for (size_t j = 0; j < Game::FIELD_SIZE.x; j++)
		{
			mBoard[i][j].Draw(id);
		}
	}

	// Next
	mNext->Draw(id);

}

void Game::SetStone(const Vec2i& pos)
{
	// �͈͊O�Ȃ疳��
	if (pos.x < TOP_LEFT_POS.x || TOP_LEFT_POS.x + STONE_SIZE.x * FIELD_SIZE.x < pos.x ||
		pos.y < TOP_LEFT_POS.y || TOP_LEFT_POS.y + STONE_SIZE.y * FIELD_SIZE.y < pos.y)
	{
		std::cout << "click position (" << pos.x << ", " << pos.y << ") is out of board.\n";
		return;
	}

	Vec2i fixedPos = pos - TOP_LEFT_POS;
	Vec2i index = fixedPos / STONE_SIZE;

	// ���łɂ����Ă������牽�����Ȃ�
	if (!IsSpaceStone(mBoard[index.y][index.x].GetType()))
	{
		std::cout << "index (" << index.x << ", " << index.y << ") already exists.\n";
		return;
	}

	// �ݒu�\�Ȃ�ݒu
	if (TryFlip(index, mTurn) > 0)
	{
		PlaceStone(index, mTurn);
		const Vec2i& score = GetCurrentScore();
		std::cout << "stone set to (" << index.x << ", " << index.y << ") successfully.\n";
			//<< "score - black: " << score.x << " white: " << score.y << "\n";

		// �^�[���I��
		SwitchTurn();
	}
	else
	{
		std::cout << "you tried to place stone to the invalid position.\n";
	}
}

// �^�[���`�F���W
void Game::SwitchTurn()
{
	switch (mTurn)
	{
	case Stone::Type::Black:
		mTurn = Stone::Type::White;
		std::cout << "Turn changed to White.\n";
		break;
	case Stone::Type::White:
		mTurn = Stone::Type::Black;
		std::cout << "Turn changed to Black.\n";
		break;
	case Stone::Type::None:
	default:
		std::cout << "Unknown turn.\n";
		break;
	}

	// �l�N�X�g�̐ݒ�
	mNext->SetType(mTurn);
}

// �w��̏ꏊ�ɐ΂�u���ĉ��Ђ�����Ԃ��邩�擾
size_t Game::TryFlip(const Vec2i& index, Stone::Type type)
{
	Stone::Type attackerType = type;
	size_t totalFlippedCount = 0;

	// �u�����Ƃ��Ă���ӏ��ɂ��łɐ΂����݂���Ώ��O
	auto nowType = mBoard[index.y][index.x].GetType();
	if (!IsSpaceStone(nowType))
	{
		return 0;
	}

	// 8������
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			// �����̃^�C�v�ɓ�����܂Ŕ��]����������
			Vec2i target = index;


			while (true)
			{
				// �i�܂���
				target += {x, y};

				// �͈͊O�Ȃ�I��
				if (target.x < 0 || FIELD_SIZE.x <= target.x ||
					target.y < 0 || FIELD_SIZE.y <= target.y)
				{
					break;
				}

				// �����̐F�������炻���܂ł𔽓]�����ďI��
				auto targetType = mBoard[target.y][target.x].GetType();
				if (targetType == attackerType)
				{
					size_t flippedCount = 0;
					// �v�Z�𐳊m�ɍs�����߂ɂ܂�1�i�߂�
					target -= {x, y};

					while (target != index)
					{
						// try�Ȃ̂Ŏ��ۂ̃t���b�v�͍s��Ȃ�
						//mBoard[target.y][target.x].SetType(attackerType);
						++flippedCount;
						target -= {x, y};
					}
					totalFlippedCount += flippedCount;
					break;
				}
				else if (IsSpaceStone(targetType))
				{
					// ��Ȃ�I��
					break;
				}
				else
				{
					// �G�̐F�Ȃ瑱����
					// do nothing
				}

			}
		}
	}

	return totalFlippedCount;
}

// ���ۂɐ΂�u���A���]��������
void Game::PlaceStone(const Vec2i& index, const Stone::Type type)
{
	if (IsSpaceStone(type))
	{
		std::cout << "you tried to flip with none. this is weird.\n";
		return;
	}

	// �܂��͒u��
	mBoard[index.y][index.x].SetType(type);

	Stone::Type attackerType = type;

	// 8������
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			// �����̃^�C�v�ɓ�����܂Ŕ��]����������
			Vec2i target = index;
			while (true)
			{
				// �i�܂���
				target += {x, y};

				// �͈͊O�Ȃ�I��
				if (target.x < 0 || FIELD_SIZE.x <= target.x ||
					target.y < 0 || FIELD_SIZE.y <= target.y)
				{
					break;
				}

				// �����̐F�������炻���܂ł𔽓]�����ďI��
				auto targetType = mBoard[target.y][target.x].GetType();
				if (targetType == attackerType)
				{
					while (target != index)
					{
						mBoard[target.y][target.x].SetType(attackerType);
						target -= {x, y};
					}
					break;
				}
				else if (IsSpaceStone(targetType))
				{
					// ��Ȃ�I��
					break;
				}
				else
				{
					// �G�̐F�Ȃ瑱����
					// do nothing
				}

			}
		}
	}

}

bool Game::IsSpaceStone(Stone::Type type) const
{
	switch (type)
	{
	case Stone::Type::Black:
	case Stone::Type::White:
		return false;
	case Stone::Type::None:
	case Stone::Type::Available:
		return true;
	default:
		return false;
	}
}

// ���݂̍��Ɣ��̐���Vec2�Ŏ擾
Vec2i Game::GetCurrentScore() const
{
	Vec2i count;
	for (size_t i = 0; i < FIELD_SIZE.y; i++)
	{
		for (size_t j = 0; j < FIELD_SIZE.x; j++)
		{
			switch (mBoard[i][j].GetType())
			{
			case Stone::Type::Black:
				++count.x;
				break;
			case Stone::Type::White:
				++count.y;
				break;
			case Stone::Type::None:
			case Stone::Type::Available:
				break;
			default:
				std::cout << "Unknown Type\n";
				break;
			}
		}
	}
	return count;
}

void Game::ResetBoard()
{
	// init field
	for (size_t i = 0; i < FIELD_SIZE.y; i++)
	{
		for (size_t j = 0; j < FIELD_SIZE.x; j++)
		{
			mBoard[i][j] = Stone(BASE_POS + Vec2f(Stone::SIZE.x / 2 * j, -Stone::SIZE.y / 2 * i), Stone::SIZE);
		}
	}

	// �ŏ��̈ʒu
	mBoard[3][3].SetType(Stone::Type::White);
	mBoard[3][4].SetType(Stone::Type::Black);
	mBoard[4][3].SetType(Stone::Type::Black);
	mBoard[4][4].SetType(Stone::Type::White);

	// �^�[���ݒ�
	mTurn = Stone::Type::Black;

	// �l�N�X�g
	mNext->SetType(Stone::Type::Black);
}

bool Game::CheckPlayable()
{
	bool isPlayable = false;
	// init field
	for (int i = 0; i < FIELD_SIZE.y; i++)
	{
		for (int j = 0; j < FIELD_SIZE.x; j++)
		{
			auto count = TryFlip({ j, i }, mTurn);
			if (count > 0)
			{
				isPlayable = true;
			}

			auto type = mBoard[i][j].GetType();
			if (IsSpaceStone(type))
			{
				mBoard[i][j].SetType(count > 0 ? Stone::Type::Available : Stone::Type::None);
			}
		}
	}

	return isPlayable;
}
