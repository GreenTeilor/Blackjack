#include <iostream>
#include <array>
#include <ctime>
#include <vector>
#include <string>



class Card
{
public:

	enum class CardSuit
	{
		SUIT_CLUB,
		SUIT_HEART,
		SUIT_SPADE,
		SUIT_DIAMOND,
		MAX_SUITS
	};

	enum class CardRank
	{
		RANK_2,
		RANK_3,
		RANK_4,
		RANK_5,
		RANK_6,
		RANK_7,
		RANK_8,
		RANK_9,
		RANK_10,
		RANK_JACKET,
		RANK_QUEEN,
		RANK_KING,
		RANK_ACE,
		MAX_RANKS
	};

private:

	CardSuit m_suit;
	CardRank m_rank;

	void printSuit(const CardSuit& suit) const
	{
		switch (suit)
		{
		case CardSuit::SUIT_CLUB:
			std::cout << "club";
			break;
		case CardSuit::SUIT_HEART:
			std::cout << "heart";
			break;
		case CardSuit::SUIT_SPADE:
			std::cout << "spade";
			break;
		case CardSuit::SUIT_DIAMOND:
			std::cout << "diamond";
			break;
		default:
			std::cout << static_cast<int>(CardSuit::MAX_SUITS);
		}
	}

	void printRank(const CardRank& suit) const
	{
		switch (suit)
		{
		case CardRank::RANK_2:
			std::cout << "2";
			break;
		case CardRank::RANK_3:
			std::cout << "3";
			break;
		case CardRank::RANK_4:
			std::cout << "4";
			break;
		case CardRank::RANK_5:
			std::cout << "5";
			break;
		case CardRank::RANK_6:
			std::cout << "6";
			break;
		case CardRank::RANK_7:
			std::cout << "7";
			break;
		case CardRank::RANK_8:
			std::cout << "8";
			break;
		case CardRank::RANK_9:
			std::cout << "9";
			break;
		case CardRank::RANK_10:
			std::cout << "10";
			break;
		case CardRank::RANK_JACKET:
			std::cout << "jacket";
			break;
		case CardRank::RANK_QUEEN:
			std::cout << "queen";
			break;
		case CardRank::RANK_KING:
			std::cout << "king";
			break;
		case CardRank::RANK_ACE:
			std::cout << "ace";
			break;
		default:
			std::cout << static_cast<int>(CardRank::MAX_RANKS);
		}
	}

public:
	Card(CardSuit suit = CardSuit::MAX_SUITS, CardRank rank = CardRank::MAX_RANKS) : m_suit{ suit }, m_rank{ rank }
	{
		
	}

	void printCard() const
	{
		printRank(m_rank);
		std::cout << " of ";
		printSuit(m_suit);
	}

	int getCardValue() const
	{
		switch (m_rank)
		{
		case CardRank::RANK_2:		return 2;
		case CardRank::RANK_3:		return 3;
		case CardRank::RANK_4:		return 4;
		case CardRank::RANK_5:		return 5;
		case CardRank::RANK_6:		return 6;
		case CardRank::RANK_7:		return 7;
		case CardRank::RANK_8:		return 8;
		case CardRank::RANK_9:		return 9;
		case CardRank::RANK_10:		return 10;
		case CardRank::RANK_JACKET:	return 10;
		case CardRank::RANK_QUEEN:	return 10;
		case CardRank::RANK_KING:	return 10;
		case CardRank::RANK_ACE:	return 11;
		}
		return 0;
	}

};

class Deck
{
private:

	using TDeck = std::array<Card, static_cast<int>(Card::CardSuit::MAX_SUITS)* static_cast<int>(Card::CardRank::MAX_RANKS)>;

	TDeck m_deck;
	Card* m_cardPtr;

	void createDeck()
	{
		for (int i = 0; i < static_cast<int>(Card::CardSuit::MAX_SUITS); ++i)
			for (int j = 0; j < static_cast<int>(Card::CardRank::MAX_RANKS); ++j)
				m_deck[i * static_cast<int>(Card::CardRank::MAX_RANKS) + j] = { static_cast<Card::CardSuit>(i), static_cast<Card::CardRank>(j) };
	}

	static void swapCard(Card& card1, Card& card2)
	{
		Card temp = card1;
		card1 = card2;
		card2 = temp;
	}

	static int genRandNum(const int min, const int max)
	{
		static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
		return static_cast<int>(rand() * fraction * (max - min + 1) + min);
	}

public:

	void shuffleDeck()
	{
		for (int i = 0; i < m_deck.size(); ++i)
			for (int j = 0; j < m_deck.size(); ++j)
				swapCard(m_deck[j], m_deck[genRandNum(0, static_cast<int>(Card::CardSuit::MAX_SUITS) * static_cast<int>(Card::CardRank::MAX_RANKS) - 1)]);
	}

	void printDeck() const
	{
		for (const Card& card : m_deck)
		{
			card.printCard();
			std::cout << std::endl;
		}
	}

	void takeCard()
	{
		m_cardPtr--;
	}

	int getTopCardValue()
	{
		return m_cardPtr->getCardValue();
	}

	Card getTopCard()
	{
		return *m_cardPtr;
	}

	Deck()
	{
		this->createDeck();
		this->shuffleDeck();
		m_cardPtr = &m_deck[m_deck.size() - 1];
	}

};

class Player
{
private:

	std::string m_name;
	std::vector<Card> m_hand;
	int m_score;

public:

	Player(std::string name = "player1", std::vector<Card> hand = {}, int score = 0) : m_name{ name }, m_hand{ hand }, m_score{ score }
	{

	}

	void addToHand(Card card)
	{
		m_hand.push_back(card);
	}

	void removeFromHand()
	{
		m_hand.pop_back();
	}

	void printHand() const
	{
		for (int i = 0; i < m_hand.size(); ++i)
		{
			m_hand[i].printCard();
			std::cout << "   ";
		}
	}

	//Change directly breaking encapsulation
	int& setScore()
	{
		return m_score;
	}

	int getScore() const
	{
		return m_score;
	}

};

bool playBlackjack(Deck deck)
{
	Player player{"player"};
	Player diller{"diller"};
	std::cout << "Diller takes card: ";
	diller.setScore() += deck.getTopCardValue();
	diller.addToHand(deck.getTopCard());
	deck.getTopCard().printCard();
	std::cout << std::endl;
	deck.takeCard();

	std::cout << "Diller takes card: "
			  << "Other diller's card is currently concealed...";
	std::cout << std::endl;
	diller.setScore() += deck.getTopCardValue();
	diller.addToHand(deck.getTopCard());
	std::cout << std::endl;
	deck.takeCard();

	bool keepTaking{ true };
	while (keepTaking)
	{
		std::cout << "Take card?:  1 - yes  0 - no: ";
		std::cin >> keepTaking;
		if (keepTaking == 1)
		{
			std::cout << "You took card: ";
			deck.getTopCard().printCard();
			std::cout << std::endl;
			player.setScore() += deck.getTopCardValue();
			player.addToHand(deck.getTopCard());
			std::cout << std::endl;
			deck.takeCard();
			std::cout << "Your hand now: ";
			player.printHand();
			std::cout << std::endl;
			if (player.getScore() > 21)
				keepTaking = false;
		}
		else 
		{
			while (diller.getScore() < 17 || diller.getScore() < player.getScore())
			{
				std::cout << std::endl;
				std::cout << "Diller takes card: ";
				deck.getTopCard().printCard();
				std::cout << std::endl;
				diller.setScore() += deck.getTopCardValue();
				diller.addToHand(deck.getTopCard());
				std::cout << "Diller's hand now: ";
				diller.printHand();
				std::cout << std::endl;
				if (diller.getScore() > 21)
					keepTaking = false;
			}
			keepTaking = false;
		}
	}
	std::cout << std::endl;
	std::cout << "Diller hand: ";
	diller.printHand();
	std::cout << std::endl;
	std::cout << "Player hand: ";
	player.printHand();
	std::cout << std::endl;
	if ((player.getScore() > diller.getScore() && player.getScore() <= 21) || (player.getScore() <= 21 && diller.getScore() > 21))
		return true;

	return false;
}

int main() 
{
	srand(time(0));
	rand();
	Deck deck;
	if (playBlackjack(deck))
		std::cout << "Player won!";
	else
		std::cout << "Diller won!";

	return 0;
}