import { Component, signal } from '@angular/core';
import { Toolbar } from './layout/toolbar/toolbar';

@Component({
  imports: [Toolbar],
  selector: 'app-root',
  styleUrl: './app.css',
  templateUrl: './app.html',
})
export class App {
  protected readonly title = signal('Client');
}
