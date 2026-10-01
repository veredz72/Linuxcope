import { Component } from '@angular/core';
import { BaseChartDirective } from 'ng2-charts';
import { ChartConfiguration, ChartData, ChartType, Plugin } from 'chart.js';

// 1. Define custom plugin (e.g., drawing a vertical reference line or watermark)
const timingHighlightPlugin: Plugin = {
  id: 'timingHighlight',
    /*beforeDraw: (chart) => {
      const { ctx, chartArea: { top, bottom }, scales: { x } } = chart;
      if (!x) return;

      // Example: Highlight region between 400ms and 600ms
      const startX = x.getPixelForValue(400);
      const endX = x.getPixelForValue(600);

      ctx.save();
      ctx.fillStyle = 'rgba(239, 68, 68, 0.1)';
      ctx.fillRect(startX, top, endX - startX, bottom - top);
      ctx.restore();
    }*/
   // 1. Capture mouse movement and leave events
  afterEvent: (chart, args) => {
    const { event } = args;
    const { chartArea } = chart;
    const chartState = chart as any;

    if (!chartArea) return;

    if (event.type === 'mousemove') {
      // Check if mouse is within chart boundaries
      if (event.x != null && event.y != null &&
        event.x >= chartArea.left &&
        event.x <= chartArea.right &&
        event.y >= chartArea.top &&
        event.y <= chartArea.bottom
      ) {
        chartState.cursorX = event.x;
      } else {
        chartState.cursorX = null;
      }
      args.changed = true; // Signals Chart.js to re-render
    } else if (event.type === 'mouseout') {
      chartState.cursorX = null;
      args.changed = true;
    }
  },

  // 2. Draw the vertical line on the canvas
  afterDraw: (chart) => {
    const chartState = chart as any;
    const { ctx, chartArea: { top, bottom } } = chart;

    if (chartState.cursorX != null) {
      ctx.save();
      ctx.beginPath();
      ctx.strokeStyle = '#ef4444'; // Line color (e.g. red)
      ctx.lineWidth = 1.5;         // Line thickness
      //ctx.setLineDash([4, 4]);     // Dashed line (remove for solid line)

      ctx.moveTo(chartState.cursorX, top);
      ctx.lineTo(chartState.cursorX, bottom);
      ctx.stroke();
      ctx.restore();
    }
  }
};

@Component({
  imports: [BaseChartDirective],
  selector: 'app-dashboard',
  styleUrl: './dashboard.css',
  templateUrl: './dashboard.html',
})
export class Dashboard {
  public chartType: ChartType = 'line';

  // Expose the plugin to the template
  public chartPlugins: Plugin[] = [timingHighlightPlugin];

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
