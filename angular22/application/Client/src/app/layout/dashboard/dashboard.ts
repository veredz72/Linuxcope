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

public readonly yCategories: string[] = ['','TMR1', 'TMR2', 'T1Isr', 'T2Isr',''];
public chartData: ChartData<'scatter'> = {
  datasets: [
    {
      label: '',
      data: [
        { x: 50, y: 1 },
        { x: 550, y: 1 },
         { x: null, y: null },
         { x: 950, y: 1 },
        { x: 1450, y: 1 },
        { x: null, y: null },
        { x: 400, y: 2 },
        { x: 600, y: 2 },
        { x: null, y: null },
        { x: 800, y: 2 },
        { x: 1000, y: 2 },
        { x: null, y: null },
        { x: 45, y: 3},
        { x: null, y: null },
        { x: 795, y: 4},
        { x: null, y: null },
        { x: 945, y: 3},
        { x: null, y: null },
        { x: 395, y: 4},
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
        min: 0,
        max: this.yCategories.length -1,
        ticks: {
          stepSize: 1,
          // 2. Map numeric indices back to readable strings on the axis
          callback: (value) => {
            console.log (value);
            const index = Number(value);
            return this.yCategories[index]; // Return the corresponding string label for the index';
          }
        },
        grid: {
          color: '#cac8c8', // X-axis grid lines
        }
      },
      x: {
        type: 'linear', // Use a linear scale for the x-axis
        min: 0,
        max: 3000,  // [msec] Set the maximum value for the x-axis
        ticks: {
          stepSize: 100 // Set the step size for the x-axis ticks
        },
        grid: {
          color: '#cac8c8', // X-axis grid lines
        }
      }
    }
  };
}
