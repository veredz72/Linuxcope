import { Component } from '@angular/core';
import { BaseChartDirective } from 'ng2-charts';
import { ChartConfiguration, ChartData, ChartType } from 'chart.js';

@Component({
  imports: [BaseChartDirective],
  selector: 'app-dashboard',
  styleUrl: './dashboard.css',
  templateUrl: './dashboard.html',
})
export class Dashboard {
  public chartType: ChartType = 'line';

  // 2. Add data and point configurations
  // Don't forget to register LineElement if importing tree-shakable elements:
// import { Chart, ScatterController, PointElement, LineElement, LinearScale, Tooltip, Legend } from 'chart.js';
// Chart.register(ScatterController, PointElement, LineElement, LinearScale, Tooltip, Legend);

public readonly yCategories: string[] = ['T1', 'T2', 'T3', 'T4', 'T5'];
public chartData: ChartData<'scatter'> = {
  datasets: [
    {
      label: 'Connected Scatter Path',
      data: [
        { x: 1, y: 1 },
        { x: 3, y: 1 },
         { x: null, y: null },
        { x: 6, y: 2 },
        { x: 8, y: 2 },
        { x: null, y: null },
        { x: 10, y: 1},
        { x: 12, y: 1 }
      ],
      // 1. Enable the line
      showLine: true,

      // 2. Line appearance
      borderColor: '#2563eb',
      borderWidth: 2,
      tension: 0, // 0 for straight segments; 0.2-0.4 for smooth bezier curves

      // 3. Dot (marker) appearance
      backgroundColor: '#ef4444',
      pointRadius: 5,
      pointHoverRadius: 7
    }
  ]
};

  public chartOptions: ChartConfiguration['options'] = {
    responsive: true,
    maintainAspectRatio: false,
    scales: {
      y: {
        type: 'linear',
        // Pin limits to prevent points on the edge from being cut off
        min: -0.5,
        max: this.yCategories.length - 0.5,
        ticks: {
          stepSize: 1,
          // 2. Map numeric indices back to readable strings on the axis
          callback: (value) => {
            const index = Number(value);
            return this.yCategories[index] ?? '';
          }
        }
      },
      x: {
        type: 'linear', // Use a linear scale for the x-axis
        min: 0,
        max: 32,
        ticks: {
          stepSize: 1 // Set the step size for the x-axis ticks
        }
      }
    }
  };
}
