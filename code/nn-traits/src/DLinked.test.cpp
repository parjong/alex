#include <gtest/gtest.h>

#include "traits/DLinked.h"

#include <memory>

using namespace traits;

namespace
{
class Instr;
class Block;

using InstrLink = DLinked<Block, Instr>::Link;
using InstrList = DLinked<Block, Instr>::List;

class Block
{
public:
  Block(InstrLink *link) : _instr{link, this}
  {
    // DO NOTHING
  }

public:
	Block(const Block &) = delete;
	Block(Block &&) = delete;

public:
  InstrList *instr(void) { return &_instr; }
  const InstrList *instr(void) const { return &_instr; }

private:
  InstrList _instr;
};

class Instr : public DLinked<Block, Instr>::Node
{
public:
  Instr(const InstrLink *link) : _link{link}
  {
    // DO NOTHING
  }

public:
	Instr(const Instr &) = delete;
	Instr(Instr &&) = delete;

private:
  void get(const InstrLink **out) const override
  {
    *out = _link;
  }

private:
  InstrList *list(void) const override
  {
    return parent()->instr();
  }

private:
  const InstrLink * const _link;
};

class DLinkedTest : public ::testing::Test
{
protected:
  InstrLink ins_link;

  Block *create_block(void)
  {
    auto p = new Block{&ins_link};
    _blocks.emplace_back(p);
    return p;
  }

  Instr *create_instr(void)
  {
    auto p = new Instr{&ins_link};
    _instrs.emplace_back(p);
    return p;
  }

private:
  std::vector<std::unique_ptr<Block>> _blocks;
  std::vector<std::unique_ptr<Instr>> _instrs;
};
}

TEST_F(DLinkedTest, parent_create)
{
  auto block = create_block();

  EXPECT_EQ(block->instr()->head(), nullptr);
  EXPECT_EQ(block->instr()->tail(), nullptr);
  EXPECT_TRUE(block->instr()->empty());
}

TEST_F(DLinkedTest, child_create)
{
  auto instr = create_instr();

  EXPECT_EQ(instr->parent(), nullptr);
  EXPECT_EQ(instr->prev(), nullptr);
  EXPECT_EQ(instr->next(), nullptr);
}

TEST_F(DLinkedTest, enlist)
{
  auto block = create_block();
  auto instr = create_instr();

  block->instr()->enlist(instr);

  EXPECT_EQ(instr->parent(), block);
  EXPECT_EQ(instr->prev(), nullptr);
  EXPECT_EQ(instr->next(), nullptr);
}

TEST_F(DLinkedTest, insert_after)
{
  auto block = create_block();
  auto instr_1 = create_instr();
  auto instr_2 = create_instr();

  block->instr()->enlist(instr_1);
  instr_2->insert_after(instr_1);

  EXPECT_EQ(instr_1->parent(), block);
  EXPECT_EQ(instr_1->prev(), nullptr);
  EXPECT_EQ(instr_1->next(), instr_2);

  EXPECT_EQ(instr_2->parent(), block);
  EXPECT_EQ(instr_2->prev(), instr_1);
  EXPECT_EQ(instr_2->next(), nullptr);
}
