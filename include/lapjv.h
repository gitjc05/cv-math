/**
 * @file lapjv.h
 * @brief Jonker-Volgenant linear assignment solver interface.
 */

#pragma once

#include <vector>

 /**
  * @brief Solver for square linear assignment problems using LAPJV phases.
  */
class LAPJV
{
public:
    using Cost = double;
    using CostMatrix = std::vector<std::vector<Cost>>;

    /**
     * @brief Solves a square minimum-cost assignment problem.
     * @param costMatrix Square row-major cost matrix.
     * @param rowToCol Receives column assigned to each row.
     * @param colToRow Receives row assigned to each column.
     * @return Total assignment cost.
     */
    [[nodiscard]] Cost solve(
        const CostMatrix& costMatrix,
        std::vector<int>& rowToCol,
        std::vector<int>& colToRow) const;
};
