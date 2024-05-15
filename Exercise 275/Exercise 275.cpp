#include <cassert>
#include <iostream>
#include <vector>
#include <chrono>

constexpr int MAX_SIZE = 18;
inline int grid_index(int x, int y) { return MAX_SIZE + x + y * MAX_SIZE * 2; }

struct Pos {
    int x, y;
    Pos(int x, int y) : x(x), y(y) {}

    int grid_index() { return ::grid_index(x, y); }
};

int balance_check_threshold;
int balance = 0;
int total_sculptures = 0;
std::vector<bool> queued; // Positions that have been added to add queue
std::vector<Pos> queue; // Candidate positions to add to the sculpture.

bool balanceable_after_adding(int x, int minx, int maxx, int num_pending) {
    int new_balance = balance + x;
    int max_delta = num_pending * (num_pending + 1) / 2;
    int min_bound = new_balance + num_pending * std::min(minx, x) - max_delta;
    int max_bound = new_balance + num_pending * std::max(maxx, x) + max_delta;

    return min_bound <= 0 && max_bound >= 0;
}

inline void enqueue(int x, int y, bool symmetry) {
    int index = grid_index(x, y);
    if (!queued[index]) {
        queued[index] = true;
        queue.emplace_back(x, y);
        if (symmetry && x != 0) {
            queued[grid_index(-x, y)] = true;
            queue.emplace_back(-x, y);
        }
    }
}

void queue_neighbours(Pos pos, bool symmetry) {
    enqueue(pos.x + 1, pos.y, symmetry);
    enqueue(pos.x - 1, pos.y, symmetry);
    enqueue(pos.x, pos.y + 1, symmetry);
    if (pos.y > 0) enqueue(pos.x, pos.y - 1, symmetry);
}

void add(Pos pos, int n, std::vector<Pos>::iterator add_from, bool symmetry, int minx, int maxx) {
    if (n <= 0) {
        if (symmetry && n == 0 || !symmetry && balance + pos.x == 0) ++total_sculptures;
        return;
    }
    if (n <= balance_check_threshold && !balanceable_after_adding(pos.x, minx, maxx, n)) {
        return;
    }

    if (!symmetry) balance += pos.x;

    int old_queue_size = queue.size();
    queue_neighbours(pos, symmetry);

    for (auto it = add_from; it != queue.end(); ) {
        Pos nxt_pos = *it;
        if (symmetry && nxt_pos.x != 0) {
            int new_maxx = std::max(maxx, abs(nxt_pos.x));
            ++it;
            assert((*it).x == -nxt_pos.x);
            ++it; // Skip this mirror-position
            add(nxt_pos, n-2, it, true, -new_maxx, new_maxx);
            add(nxt_pos, n-1, it, false, std::min(minx, nxt_pos.x), std::max(maxx, nxt_pos.x));
        } else {
            ++it;
            add(nxt_pos, n-1, it, symmetry, std::min(minx, nxt_pos.x), std::max(maxx, nxt_pos.x));
        }
    }

    if (!symmetry) balance -= pos.x;

    while (queue.size() > old_queue_size) {
        queued[queue.back().grid_index()] = false;
        queue.pop_back();
    }
}

int generate_all(int size) {
    balance_check_threshold = size / 2;

    queue.reserve(size * 4); // Prevent resizing during search so that iterators remain valid
    queued.resize(MAX_SIZE * 2 * (MAX_SIZE + 1), false);

    total_sculptures = 0;

    Pos start_pos(0, 0);
    queued[start_pos.grid_index()] = true;
    add(start_pos, size - 1, queue.begin(), true, 0, 0);

    return total_sculptures;
}

int main(int argc, char** argv) {
    auto start = std::chrono::high_resolution_clock::now();
    int num = generate_all(18);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Total = " << num << ", Time taken = " << duration.count() << "ms\n";
}