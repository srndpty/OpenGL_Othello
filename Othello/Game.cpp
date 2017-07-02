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
	// 盤面
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
	// 範囲外なら無効
	if (pos.x < TOP_LEFT_POS.x || TOP_LEFT_POS.x + STONE_SIZE.x * FIELD_SIZE.x < pos.x ||
		pos.y < TOP_LEFT_POS.y || TOP_LEFT_POS.y + STONE_SIZE.y * FIELD_SIZE.y < pos.y)
	{
		std::cout << "click position (" << pos.x << ", " << pos.y << ") is out of board.\n";
		return;
	}

	Vec2i fixedPos = pos - TOP_LEFT_POS;
	Vec2i index = fixedPos / STONE_SIZE;

	// すでにおいてあったら何もしない
	if (!IsSpaceStone(mBoard[index.y][index.x].GetType()))
	{
		std::cout << "index (" << index.x << ", " << index.y << ") already exists.\n";
		return;
	}

	// 設置可能なら設置
	if (TryFlip(index, mTurn) > 0)
	{
		PlaceStone(index, mTurn);
		const Vec2i& score = GetCurrentScore();
		std::cout << "stone set to (" << index.x << ", " << index.y << ") successfully.\n";
			//<< "score - black: " << score.x << " white: " << score.y << "\n";

		// ターン終了
		SwitchTurn();
	}
	else
	{
		std::cout << "you tried to place stone to the invalid position.\n";
	}
}

// ターンチェンジ
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

	// ネクストの設定
	mNext->SetType(mTurn);
}

// 指定の場所に石を置いて何個ひっくり返せるか取得
size_t Game::TryFlip(const Vec2i& index, Stone::Type type)
{
	Stone::Type attackerType = type;
	size_t totalFlippedCount = 0;

	// 置こうとしている箇所にすでに石が存在すれば除外
	auto nowType = mBoard[index.y][index.x].GetType();
	if (!IsSpaceStone(nowType))
	{
		return 0;
	}

	// 8方向へ
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			// 自分のタイプに当たるまで反転させ続ける
			Vec2i target = index;


			while (true)
			{
				// 進ませる
				target += {x, y};

				// 範囲外なら終了
				if (target.x < 0 || FIELD_SIZE.x <= target.x ||
					target.y < 0 || FIELD_SIZE.y <= target.y)
				{
					break;
				}

				// 自分の色だったらそこまでを反転させて終了
				auto targetType = mBoard[target.y][target.x].GetType();
				if (targetType == attackerType)
				{
					size_t flippedCount = 0;
					// 計算を正確に行うためにまず1つ進める
					target -= {x, y};

					while (target != index)
					{
						// tryなので実際のフリップは行わない
						//mBoard[target.y][target.x].SetType(attackerType);
						++flippedCount;
						target -= {x, y};
					}
					totalFlippedCount += flippedCount;
					break;
				}
				else if (IsSpaceStone(targetType))
				{
					// 空なら終了
					break;
				}
				else
				{
					// 敵の色なら続ける
					// do nothing
				}

			}
		}
	}

	return totalFlippedCount;
}

// 実際に石を置き、反転もさせる
void Game::PlaceStone(const Vec2i& index, const Stone::Type type)
{
	if (IsSpaceStone(type))
	{
		std::cout << "you tried to flip with none. this is weird.\n";
		return;
	}

	// まずは置く
	mBoard[index.y][index.x].SetType(type);

	Stone::Type attackerType = type;

	// 8方向へ
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			// 自分のタイプに当たるまで反転させ続ける
			Vec2i target = index;
			while (true)
			{
				// 進ませる
				target += {x, y};

				// 範囲外なら終了
				if (target.x < 0 || FIELD_SIZE.x <= target.x ||
					target.y < 0 || FIELD_SIZE.y <= target.y)
				{
					break;
				}

				// 自分の色だったらそこまでを反転させて終了
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
					// 空なら終了
					break;
				}
				else
				{
					// 敵の色なら続ける
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

// 現在の黒と白の数をVec2で取得
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

	// 最初の位置
	mBoard[3][3].SetType(Stone::Type::White);
	mBoard[3][4].SetType(Stone::Type::Black);
	mBoard[4][3].SetType(Stone::Type::Black);
	mBoard[4][4].SetType(Stone::Type::White);

	// ターン設定
	mTurn = Stone::Type::Black;

	// ネクスト
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
