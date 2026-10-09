import { Component } from '@angular/core';
import { BaseChartDirective } from 'ng2-charts';
import { ChartConfiguration, ChartData, ChartType, Plugin } from 'chart.js';
import {Icd} from '../../icd/Icd'

enum MarkerState {
  Undefined,  // 0
  FromX,    // 1
  ToX,  // 2
}

@Component({
  imports: [BaseChartDirective],
  selector: 'app-dashboard',
  styleUrl: './dashboard.css',
  templateUrl: './dashboard.html',
})
export class Dashboard {
  public chartType: ChartType = 'line';

  constructor ()
  {
    
  }
  // Expose the plugin to the template
  

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
      backgroundColor: '#2563eb',
      pointRadius: 3,
      pointHoverRadius: 5
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
          stepSize: 500 // Set the step size for the x-axis ticks
        },
        grid: {
          color: '#cac8c8', // X-axis grid lines
        }
      }
    }
  };

  private markerState : MarkerState = MarkerState.Undefined;
  private fromX : number = 0;
  private toX : number = 0;

  public timingHighlightPlugin: Plugin = {
    id: 'timingHighlight',
    
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
      } 
      else if (event.type === 'mouseout') 
      {
        chartState.cursorX = null;
        args.changed = true;
      }
      else if (event.type === 'click')
      {
        if (this.markerState == MarkerState.Undefined)
        {
          this.markerState = MarkerState.FromX;
          this.fromX = chartState.cursorX;
        }
        else if (this.markerState == MarkerState.FromX)
        {
          this.toX = chartState.cursorX;
          this.markerState = MarkerState.ToX;
          //Display the time difference between the two markers
        }
        else if (this.markerState == MarkerState.ToX)
        {
          this.markerState = MarkerState.Undefined;
        }
      }
    },

    // 2. Draw the vertical line on the canvas
    afterDraw: (chart) => {
      const chartState = chart as any;
      const { ctx, chartArea: { top, bottom } } = chart;

      //draw cursor line
      if (chartState.cursorX != null) {
        this.drawLine (ctx, chartState.cursorX, top, chartState.cursorX, bottom, '#ef4444', 1.5, false);
      }

      //draw 'from' line 
      if (this.markerState==MarkerState.FromX || this.markerState==MarkerState.ToX) {
        this.drawLine (ctx, this.fromX, top, this.fromX, bottom, '#e67e22', 1.5, true);
      }

      //draw 'to' line
      if (this.markerState==MarkerState.ToX) {
        this.drawLine (ctx, this.toX, top, this.toX, bottom, '#0288d1', 1.5, true);
      }
    }
  }

  public chartPlugins: Plugin[] = [this.timingHighlightPlugin];

  private drawLine (ctx : any, fromX : number, fromY: number, toX : number, toY : number, color : string, width : number, dash : boolean)
  {
    ctx.save();
    ctx.beginPath();
    ctx.strokeStyle = color;
    ctx.lineWidth = 1.5;
    if (dash==true)
      ctx.setLineDash([4, 4]);
    ctx.moveTo(fromX, fromY);
    ctx.lineTo(toX, toY);
    ctx.stroke();
    ctx.restore();
  }

}
