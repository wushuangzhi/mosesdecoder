#include <boost/foreach.hpp>
#include "Hypothesis.h"
#include "Manager.h"
#include "ActiveChart.h"
#include "../System.h"
#include "../Scores.h"
#include "../FF/StatefulFeatureFunction.h"

using namespace std;

namespace Moses2
{
namespace SCFG
{
Hypothesis::Hypothesis(MemPool &pool,
    const System &system)
:HypothesisBase(pool, system)
{

}

void Hypothesis::Init(SCFG::Manager &mgr,
    const InputPathBase &path,
    const SCFG::SymbolBind &symbolBind,
    const SCFG::TargetPhraseImpl &tp,
    const std::vector<size_t> &prevHyposIndices)
{
  m_mgr = &mgr;
  m_symbolBind = &symbolBind;
  m_targetPhrase = &tp;

  //cerr << "symbolBind.numNT=" << symbolBind.numNT << endl;
  m_prevHypos.resize(symbolBind.numNT);

  size_t currInd = 0;
  for (size_t i = 0; i < symbolBind.coll.size(); ++i) {
    const SymbolBindElement &ele = symbolBind.coll[i];
    //cerr << "ele=" << ele.word->isNonTerminal << " " << ele.hypos << endl;

    if (ele.hypos) {
      const Hypotheses &sortedHypos = ele.hypos->GetSortedAndPruneHypos(mgr, mgr.arcLists);

      size_t prevHyposInd = prevHyposIndices[currInd];
      assert(prevHyposInd < sortedHypos.size());

      const Hypothesis *prevHypo = static_cast<const SCFG::Hypothesis*>(sortedHypos[prevHyposInd]);
      m_prevHypos[currInd] = prevHypo;

      ++currInd;
    }
  }
}

SCORE Hypothesis::GetFutureScore() const
{
  return GetScores().GetTotalScore();
}

void Hypothesis::EvaluateWhenApplied()
{
  const std::vector<const StatefulFeatureFunction*> &sfffs =
      GetManager().system.featureFunctions.GetStatefulFeatureFunctions();
  BOOST_FOREACH(const StatefulFeatureFunction *sfff, sfffs){
    //EvaluateWhenApplied(*sfff);
  }
//cerr << *this << endl;

}

}
}
