# Catapult System

This project simulates a catapult trajectory and estimates model parameters using measured launch angles and distances.

## What it does
- Reads input data from `input.csv`
- Simulates projectile motion with drag using Euler integration
- Searches for the best initial velocity `v0` and drag coefficient `k`
- Writes trajectory output to `plot.csv` for plotting

## Files
- `program.cpp` — main simulation code
- `input.csv` — CSV data with launch angle and measured distance
- `plot.csv` — generated trajectory data for plotting

## Usage
1. Build the program with your C++ compiler.
2. Place launch data in `input.csv` as `d,f` with degrees and distances.
3. Run the executable.
4. Read the best-fit parameters from console output and use `plot.csv` for plotting.

## Notes
- The simulation uses a fixed timestep (`dt`) and simple Euler integration.
- `get_plot()` generates time-series trajectory data.
- `run_calc()` evaluates candidate `v0`/`k` pairs against the input data.