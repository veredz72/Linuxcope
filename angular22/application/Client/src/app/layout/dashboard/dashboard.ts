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
  public chartData: ChartData<'line'> = {
    labels: ['1', '2', '3', '4', '5', '6', '7', '8', '9','10','11','12'],
    datasets: [
      {
        data: [65, 65, null, 80, 80, null, 50,50,null,65,65, null, 80, 80, null, 50,50,null,65,65, null, 80, 80, null, 50,50,null],
        label: 'Series A',
        fill: false,
        tension: 0.3, // Curve smoothing (0 for straight lines)
        borderColor: '#3b82f6',
        backgroundColor: 'rgba(59, 130, 246, 0.2)',

        // Point styling:
        pointRadius: 6,                // Size of the points
        pointHoverRadius: 9,           // Size on hover
        pointBackgroundColor: '#ffffff',
        pointBorderColor: '#1d4ed8',
        pointBorderWidth: 2,
        pointStyle: 'circle',          // 'circle', 'triangle', 'rect', 'cross', etc.
      },
    ],
  };

  public chartOptions: ChartConfiguration['options'] = {
    responsive: true,
    maintainAspectRatio: false,
    scales: {
      y: {
        beginAtZero: true,
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
