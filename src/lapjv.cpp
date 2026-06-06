/**
 * @file lapjv.cpp
 * @brief Jonker-Volgenant assignment solver implementation.
 */

#include "lapjv.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace
{
    /**
     * @brief Validates the square row-major cost matrix.
     */
    void validateCostMatrix(const LAPJV::CostMatrix& costMatrix)
    {
        const std::size_t dim = costMatrix.size();
        for (const std::vector<LAPJV::Cost>& row : costMatrix)
        {
            if (row.size() != dim)
            {
                throw std::invalid_argument("LAPJV requires a square cost matrix");
            }
            for (const LAPJV::Cost value : row)
            {
                if (!std::isfinite(value))
                {
                    throw std::invalid_argument("LAPJV costs must be finite");
                }
            }
        }
    }
} // namespace

LAPJV::Cost LAPJV::solve(
    const CostMatrix& costMatrix,
    std::vector<int>& rowToCol,
    std::vector<int>& colToRow) const
{
    validateCostMatrix(costMatrix);

    const int dim = static_cast<int>(costMatrix.size());
    rowToCol.assign(static_cast<std::size_t>(dim), -1);
    colToRow.assign(static_cast<std::size_t>(dim), -1);
    if (dim == 0)
    {
        return 0.0;
    }
    if (dim == 1)
    {
        rowToCol[0] = 0;
        colToRow[0] = 0;
        return costMatrix[0][0];
    }

    constexpr Cost kBig = std::numeric_limits<Cost>::max() / 4.0;
    std::vector<Cost> columnReduction(static_cast<std::size_t>(dim), 0.0);
    std::vector<Cost> rowReduction(static_cast<std::size_t>(dim), 0.0);
    std::vector<Cost> distance(static_cast<std::size_t>(dim), 0.0);
    std::vector<int> predecessor(static_cast<std::size_t>(dim), -1);
    std::vector<int> freeRows(static_cast<std::size_t>(dim), -1);
    std::vector<int> columnList(static_cast<std::size_t>(dim), -1);
    std::vector<int> matches(static_cast<std::size_t>(dim), 0);

    int freeCount = 0;

    for (int col = dim - 1; col >= 0; --col)
    {
        int minRow = 0;
        Cost minCost = costMatrix[0][static_cast<std::size_t>(col)];
        for (int row = 1; row < dim; ++row)
        {
            const Cost candidate = costMatrix[static_cast<std::size_t>(row)]
                [static_cast<std::size_t>(col)];
            if (candidate < minCost)
            {
                minCost = candidate;
                minRow = row;
            }
        }

        columnReduction[static_cast<std::size_t>(col)] = minCost;
        if (++matches[static_cast<std::size_t>(minRow)] == 1)
        {
            rowToCol[static_cast<std::size_t>(minRow)] = col;
            colToRow[static_cast<std::size_t>(col)] = minRow;
        } else if (
            minCost <
            columnReduction[static_cast<std::size_t>(rowToCol[static_cast<std::size_t>(minRow)])])
        {
            const int oldCol = rowToCol[static_cast<std::size_t>(minRow)];
            rowToCol[static_cast<std::size_t>(minRow)] = col;
            colToRow[static_cast<std::size_t>(col)] = minRow;
            colToRow[static_cast<std::size_t>(oldCol)] = -1;
        } else
        {
            colToRow[static_cast<std::size_t>(col)] = -1;
        }
    }

    for (int row = 0; row < dim; ++row)
    {
        if (matches[static_cast<std::size_t>(row)] == 0)
        {
            freeRows[static_cast<std::size_t>(freeCount++)] = row;
        } else if (matches[static_cast<std::size_t>(row)] == 1)
        {
            const int assignedCol = rowToCol[static_cast<std::size_t>(row)];
            Cost minReducedCost = kBig;
            for (int col = 0; col < dim; ++col)
            {
                if (col == assignedCol)
                {
                    continue;
                }
                minReducedCost = std::min(
                    minReducedCost,
                    costMatrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)] -
                    columnReduction[static_cast<std::size_t>(col)]);
            }
            columnReduction[static_cast<std::size_t>(assignedCol)] -= minReducedCost;
        }
    }

    for (int pass = 0; pass < 2; ++pass)
    {
        int readIndex = 0;
        const int previousFreeCount = freeCount;
        freeCount = 0;

        while (readIndex < previousFreeCount)
        {
            const int row = freeRows[static_cast<std::size_t>(readIndex++)];
            int bestCol = 0;
            int secondBestCol = -1;
            Cost best = costMatrix[static_cast<std::size_t>(row)][0] - columnReduction[0];
            Cost secondBest = kBig;

            for (int col = 1; col < dim; ++col)
            {
                const Cost reduced =
                    costMatrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)] -
                    columnReduction[static_cast<std::size_t>(col)];
                if (reduced < secondBest)
                {
                    if (reduced >= best)
                    {
                        secondBest = reduced;
                        secondBestCol = col;
                    } else
                    {
                        secondBest = best;
                        secondBestCol = bestCol;
                        best = reduced;
                        bestCol = col;
                    }
                }
            }

            int displacedRow = colToRow[static_cast<std::size_t>(bestCol)];
            if (best < secondBest)
            {
                columnReduction[static_cast<std::size_t>(bestCol)] -= secondBest - best;
            } else if (displacedRow > -1 && secondBestCol > -1)
            {
                bestCol = secondBestCol;
                displacedRow = colToRow[static_cast<std::size_t>(bestCol)];
            }

            rowToCol[static_cast<std::size_t>(row)] = bestCol;
            colToRow[static_cast<std::size_t>(bestCol)] = row;

            if (displacedRow > -1)
            {
                if (best < secondBest)
                {
                    freeRows[static_cast<std::size_t>(--readIndex)] = displacedRow;
                } else
                {
                    freeRows[static_cast<std::size_t>(freeCount++)] = displacedRow;
                }
            }
        }
    }

    for (int freeIndex = 0; freeIndex < freeCount; ++freeIndex)
    {
        const int freeRow = freeRows[static_cast<std::size_t>(freeIndex)];

        for (int col = dim - 1; col >= 0; --col)
        {
            distance[static_cast<std::size_t>(col)] =
                costMatrix[static_cast<std::size_t>(freeRow)][static_cast<std::size_t>(col)] -
                columnReduction[static_cast<std::size_t>(col)];
            predecessor[static_cast<std::size_t>(col)] = freeRow;
            columnList[static_cast<std::size_t>(col)] = col;
        }

        int low = 0;
        int up = 0;
        int last = -1;
        int endOfPath = -1;
        Cost minDistance = 0.0;
        bool unassignedFound = false;

        do
        {
            if (up == low)
            {
                last = low - 1;
                minDistance = distance[static_cast<std::size_t>(columnList[static_cast<std::size_t>(up++)])];

                for (int scan = up; scan < dim; ++scan)
                {
                    const int col = columnList[static_cast<std::size_t>(scan)];
                    const Cost candidate = distance[static_cast<std::size_t>(col)];
                    if (candidate <= minDistance)
                    {
                        if (candidate < minDistance)
                        {
                            up = low;
                            minDistance = candidate;
                        }
                        columnList[static_cast<std::size_t>(scan)] =
                            columnList[static_cast<std::size_t>(up)];
                        columnList[static_cast<std::size_t>(up++)] = col;
                    }
                }

                for (int scan = low; scan < up; ++scan)
                {
                    const int col = columnList[static_cast<std::size_t>(scan)];
                    if (colToRow[static_cast<std::size_t>(col)] < 0)
                    {
                        endOfPath = col;
                        unassignedFound = true;
                        break;
                    }
                }
            }

            if (!unassignedFound)
            {
                const int col1 = columnList[static_cast<std::size_t>(low++)];
                const int row = colToRow[static_cast<std::size_t>(col1)];
                const Cost reducedBase =
                    costMatrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(col1)] -
                    columnReduction[static_cast<std::size_t>(col1)] - minDistance;

                for (int scan = up; scan < dim; ++scan)
                {
                    const int col = columnList[static_cast<std::size_t>(scan)];
                    const Cost candidate =
                        costMatrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)] -
                        columnReduction[static_cast<std::size_t>(col)] - reducedBase;

                    if (candidate < distance[static_cast<std::size_t>(col)])
                    {
                        predecessor[static_cast<std::size_t>(col)] = row;
                        if (candidate == minDistance)
                        {
                            if (colToRow[static_cast<std::size_t>(col)] < 0)
                            {
                                endOfPath = col;
                                unassignedFound = true;
                                break;
                            }
                            columnList[static_cast<std::size_t>(scan)] =
                                columnList[static_cast<std::size_t>(up)];
                            columnList[static_cast<std::size_t>(up++)] = col;
                        }
                        distance[static_cast<std::size_t>(col)] = candidate;
                    }
                }
            }
        } while (!unassignedFound);

        for (int scan = last; scan >= 0; --scan)
        {
            const int col = columnList[static_cast<std::size_t>(scan)];
            columnReduction[static_cast<std::size_t>(col)] +=
                distance[static_cast<std::size_t>(col)] - minDistance;
        }

        int row = -1;
        do
        {
            row = predecessor[static_cast<std::size_t>(endOfPath)];
            colToRow[static_cast<std::size_t>(endOfPath)] = row;
            const int nextCol = rowToCol[static_cast<std::size_t>(row)];
            rowToCol[static_cast<std::size_t>(row)] = endOfPath;
            endOfPath = nextCol;
        } while (row != freeRow);
    }

    Cost totalCost = 0.0;
    for (int row = 0; row < dim; ++row)
    {
        const int col = rowToCol[static_cast<std::size_t>(row)];
        rowReduction[static_cast<std::size_t>(row)] =
            costMatrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)] -
            columnReduction[static_cast<std::size_t>(col)];
        totalCost += costMatrix[static_cast<std::size_t>(row)][static_cast<std::size_t>(col)];
    }

    return totalCost;
}
