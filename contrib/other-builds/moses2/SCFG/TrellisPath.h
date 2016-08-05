/*
 * TrellisPath.h
 *
 *  Created on: 2 Aug 2016
 *      Author: hieu
 */
#pragma once
#include "../ArcLists.h"
#include "../TypeDef.h"
#include "../Vector.h"

namespace Moses2
{
class Scores;
class System;

template<typename T>
class TrellisPaths;

namespace SCFG
{
class Manager;
class Hypothesis;

/////////////////////////////////////////////////////////////////////
class TrellisNode
{
public:
  typedef std::vector<const TrellisNode*> Children;

  const ArcList &arcList;
  size_t ind;

  TrellisNode(MemPool &pool, const ArcLists &arcLists, const SCFG::Hypothesis &hypo);
  TrellisNode(MemPool &pool, const ArcLists &arcLists, const ArcList &varcList, size_t vind);

  TrellisNode(MemPool &pool, const ArcLists &arcLists, const TrellisNode &orig, const TrellisNode &nodeToChange);
  virtual ~TrellisNode();

  const SCFG::Hypothesis &GetHypothesis() const;
  bool HasMore() const;
  const Children &GetChildren() const
  { return m_prevNodes; }

  void OutputToStream(std::stringstream &strm) const;

protected:
  Children m_prevNodes;

  void CreateTail(MemPool &pool, const ArcLists &arcLists, const SCFG::Hypothesis &hypo);
};

/////////////////////////////////////////////////////////////////////
class TrellisPath
{
public:

  TrellisPath(const SCFG::Manager &mgr, const SCFG::Hypothesis &hypo); // create best path
  TrellisPath(const SCFG::Manager &mgr, const SCFG::TrellisPath &origPath, const TrellisNode &nodeToChange); // create original path
  ~TrellisPath();

  std::string Output() const;

  const Scores &GetScores() const
  { return *m_scores; }
  Scores &GetScores()
  { return *m_scores; }

  SCORE GetFutureScore() const;

  //! create a set of next best paths by wiggling 1 of the node at a time.
  void CreateDeviantPaths(TrellisPaths<SCFG::TrellisPath> &paths, const SCFG::Manager &mgr) const;

  std::string Debug(const System &system) const;

protected:
  Scores *m_scores;
  TrellisNode *m_node;
  TrellisNode *m_prevNodeChanged;

  void CreateDeviantPaths(
      TrellisPaths<SCFG::TrellisPath> &paths,
      const SCFG::Manager &mgr,
      const TrellisNode &parentNode) const;

};

} // namespace
}

