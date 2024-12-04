import numpy as np
from ga_trajopt import GATrajectoryOptimizer


class GATrajectoryOptimizerSolution(GATrajectoryOptimizer):

    def fitness(self, x):
        fit = 0
        # --- Your code here

        x_cum = self.start + np.cumsum(x, axis=0)

        dist2goal = np.linalg.norm(x_cum[-1,:] - self.goal)**2
        delta_x = np.sum(np.linalg.norm(x, axis=1)**2)

        I_obstacle = 0
        for centre, radius in zip(self.obstacle_centres, self.obstacle_radii):
            I_obstacle += np.sum(np.where(np.linalg.norm(x_cum - centre, axis = 1) <= radius, 1, 0)))

        fit = -(dist2goal + delta_x + 100*I_obstacle)

        # ---
        return fit

    def crossover(self, parent1, parent2, crossover_point):
        child1, child2 = None, None
        # --- Your code here

        child1 = np.vstack((parent1[0:crossover_point, :], parent2[crossover_point:, :]))
        child2 = np.vstack((parent2[0:crossover_point, :], parent1[crossover_point:, :]))

        # ---
        return child1, child2

    def select_children(self, parent, child):

        chosen, fitness = None, None

        # --- Your code here

        fitness_parent = self.fitness(parent)
        fitness_child = self.fitness(child)
        fitnesses = [fitness_parent, fitness_child]
        choice = [parent, child]
        sorted_idx = np.argsort(fitnesses)
        ran = np.random.rand()
        if ran < self.params['select_best_child_p']:
            fitness = fitnesses[sorted_idx[-1]]
            chosen = choice[sorted_idx[-1]]
        else:
            fitness = fitnesses[sorted_idx[-2]]
            chosen = choice[sorted_idx[-2]]

        # ---
        return chosen, fitness


if __name__ == "__main__":
    # GA path planning

    # Setup start, goal and spherical obstacles
    goal = np.array([1.0, 1.0])
    start = np.array([0.0, 0.0])
    obstacle_centres = np.array([
        [0.5, 0.2],
        [0.2, 0.8]
    ])
    obstacle_radii = np.array([0.25, 0.15])

    # Solver parameters
    N = 500
    T = 20
    params = {
        'N': 500,
        'iters': 100,
        'cross_over_p': 0.5,
        'mutate_p': 0.5,
        'select_best_parent_p': 0.9,
        'select_best_child_p': 0.9
    }

    solver = GATrajectoryOptimizerSolution(start, goal, obstacle_radii, obstacle_centres, T, params)
    # Solve to get best trajectory and plot
    best = solver.solve()
    solver.plot_trajectory(best)
