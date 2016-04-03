#include "TraditionalGame.h"

#include <algorithm>


namespace {

bool checkGameWonInDirection(const ttt::Vec2& pos,
			     int& winner,
			     std::vector<ttt::Vec2>& winner_positions,
			     const ttt::Vec2& dir,
			     std::shared_ptr<const ttt::Board> board,
			     unsigned int length_to_win)
{
  using namespace ttt;
  
  winner = board->get(pos);
  if(winner == 0)
    return false;

  winner_positions.clear();
  winner_positions.push_back(pos);
  
  Vec2 forward_pos = pos + dir;
  for (; board->get(forward_pos) == winner; forward_pos += dir)
  {
    winner_positions.push_back(forward_pos);
  }

  std::reverse(winner_positions.begin(), winner_positions.end());
  
  Vec2 backward_pos = pos - dir;
  for (; board->get(backward_pos) == winner; backward_pos -= dir)
  {
    winner_positions.push_back(backward_pos);
  }

  return winner_positions.size() >= length_to_win;
}

}

namespace ttt {

TraditionalGame::TraditionalGame(std::shared_ptr<Board> board,
				 int num_of_players,
				 int length_to_win)
  : Game(board, num_of_players),
    m_length_to_win(length_to_win)
{
}

TraditionalGame::TraditionalGame(const TraditionalGame& other)
  : Game(other),
    m_length_to_win(other.m_length_to_win)
{
}

TraditionalGame::TraditionalGame(TraditionalGame&& other)
  : Game(other),
    m_length_to_win(other.m_length_to_win)
{
}

TraditionalGame::~TraditionalGame()
{
}

bool TraditionalGame::isLegal(const Vec2& pos,
			      int player) const
{
  return getBoard()->get(pos) == 0;
}

bool TraditionalGame::isGameOver(int& winner,
				 std::vector<Vec2>& winner_positions) const
{
  // TODO.
}

std::shared_ptr<Game> TraditionalGame::clone() const
{
  return std::make_shared<TraditionalGame>(*this);
}

bool TraditionalGame::isGameWonAt(const Vec2& pos,
		 int& winner,
		 std::vector<Vec2>& winner_positions) const
{
  static const std::vector<Vec2> directions {Vec2(1, 0), Vec2(0, 1),
                                             Vec2(1, 1), Vec2(1, -1)};
  std::shared_ptr<const Board> board = getBoard();
  
  for (const Vec2& dir : directions)
  {
    bool won = checkGameWonInDirection(pos, winner, winner_positions,
				       dir, board, m_length_to_win);
    if (won)
      return true;
  }

  return false;
}

} // namespace ttt.
