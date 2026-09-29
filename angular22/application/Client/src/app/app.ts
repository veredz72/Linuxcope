import { Component, signal } from '@angular/core';
import { Toolbar } from './layout/toolbar/toolbar';
import { Dashboard } from './layout/dashboard/dashboard';

@Component({
  imports: [Toolbar, Dashboard],
  selector: 'app-root',
  styleUrl: './app.css',
  templateUrl: './app.html',
})
export class App {
  protected readonly title = signal('Client');
}
