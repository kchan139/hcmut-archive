import clsx from "clsx";
import { useMediaQuery } from "hooks";
import { IconArrowLeft, IconArrowRight } from "icons";
import { Button } from "primitives";
import type React from "react";
import "./pagination.css";

export type PaginationProps = React.ComponentPropsWithoutRef<"nav">;
export function Pagination({
  "aria-label": ariaLabel = "Page navigation",
  className,
  ...props
}: PaginationProps) {
  const classNames = clsx("pagination");
  return <nav aria-label={ariaLabel} {...props} className={classNames} />;
}

export function PaginationPrevious({
  href = null,
  children = "Previous",
  onPress,
}: {
  href?: string | null;
  children?: React.ReactNode;
  onPress?: () => void;
}) {
  return (
    <Button
      {...(href === null ? { disabled: true } : { href })}
      variant="subtle"
      aria-label="Previous page"
      onPress={onPress}
    >
      <IconArrowLeft />
      {children}
    </Button>
  );
}

export function PaginationNext({
  href = null,
  children = "Next",
  onPress,
}: {
  href?: string | null;
  children?: React.ReactNode;
  onPress?: () => void;
}) {
  return (
    <Button
      {...(href === null ? { disabled: true } : { href })}
      variant="subtle"
      aria-label="Next page"
      onPress={onPress}
    >
      {children}
      <IconArrowRight />
    </Button>
  );
}

export function PaginationList({ children }: { children: React.ReactNode }) {
  const { isTabletUp } = useMediaQuery();
  return isTabletUp && <span className="pagination-list">{children}</span>;
}

export function PaginationPage({
  href,
  children,
  current = false,
  onPress,
}: {
  href: string;
  children: string;
  current?: boolean;
  onPress?: () => void;
}) {
  return (
    <Button
      href={href}
      aria-label={`Page ${children}`}
      aria-current={current ? "page" : undefined}
      variant={current ? "neutral" : "subtle"}
      className={clsx()}
      onPress={onPress}
    >
      <span className="">{children}</span>
    </Button>
  );
}

export function PaginationGap() {
  return (
    <div aria-hidden="true" className="">
      &hellip;
    </div>
  );
}
